#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int asprintf (char**,char*,int,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* checked_strdup (char const*) ; 
 char* defined_find (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isalnum (char) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int /*<<< orphan*/  log_warnx (char*,...) ; 
 int strlen (char const*) ; 
 char* strndup (char const*,int) ; 

char *
defined_expand(const char *string)
{
	const char *value;
	char c, *expanded, *name;
	int i, ret, before_len = 0, name_off = 0, name_len = 0, after_off = 0;
	bool backslashed = false, bracketed = false;

	expanded = checked_strdup(string);

	for (i = 0; string[i] != '\0'; i++) {
		c = string[i];
		if (c == '\\' && backslashed == false) {
			backslashed = true;
			continue;
		}
		if (backslashed) {
			backslashed = false;
			continue;
		}
		backslashed = false;
		if (c != '$')
			continue;

		/*
		 * The 'before_len' variable contains the number
		 * of characters before the '$'.
		 */
		before_len = i;
		assert(i + 1 < (int)strlen(string));
		if (string[i + 1] == '{')
			bracketed = true;

		if (string[i + 1] == '\0') {
			log_warnx("truncated variable");
			return (NULL);
		}

		/*
		 * Skip '$'.
		 */
		i++;

		if (bracketed) {
			if (string[i + 1] == '\0') {
				log_warnx("truncated variable");
				return (NULL);
			}

			/*
			 * Skip '{'.
			 */
			i++;
		}

		/*
		 * The 'name_off' variable contains the number
		 * of characters before the variable name,
		 * including the "$" or "${".
		 */
		name_off = i;

		for (; string[i] != '\0'; i++) {
			c = string[i];
			/*
			 * XXX: Decide on the set of characters that can be
			 *	used in a variable name.
			 */
			if (isalnum(c) || c == '_')
				continue;

			/*
			 * End of variable name.
			 */
			if (bracketed) {
				if (c != '}')
					continue;

				/*
				 * The 'after_off' variable contains the number
				 * of characters before the rest of the string,
				 * i.e. after the variable name.
				 */
				after_off = i + 1;
				assert(i > 1);
				assert(i - 1 > name_off);
				name_len = i - name_off;
				break;
			}

			after_off = i;
			assert(i > 1);
			assert(i > name_off);
			name_len = i - name_off;
			break;
		}

		name = strndup(string + name_off, name_len);
		if (name == NULL)
			log_err(1, "strndup");
		value = defined_find(name);
		if (value == NULL) {
			log_warnx("undefined variable ${%s}", name);
			return (NULL);
		}

		/*
		 * Concatenate it back.
		 */
		ret = asprintf(&expanded, "%.*s%s%s",
		    before_len, string, value, string + after_off);
		if (ret < 0)
			log_err(1, "asprintf");

		//log_debugx("\"%s\" expanded to \"%s\"", string, expanded);
		free(name);

		/*
		 * Figure out where to start searching for next variable.
		 */
		string = expanded;
		i = before_len + strlen(value);
		backslashed = bracketed = false;
		before_len = name_off = name_len = after_off = 0;
		assert(i <= (int)strlen(string));
	}

	if (before_len != 0 || name_off != 0 || name_len != 0 || after_off != 0) {
		log_warnx("truncated variable");
		return (NULL);
	}

	return (expanded);
}