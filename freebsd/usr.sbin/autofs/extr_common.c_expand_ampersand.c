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
 int asprintf (char**,char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* checked_strdup (char*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static char *
expand_ampersand(char *string, const char *key)
{
	char c, *expanded;
	int i, ret, before_len = 0;
	bool backslashed = false;

	assert(key[0] != '\0');

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
		if (c != '&')
			continue;

		/*
		 * The 'before_len' variable contains the number
		 * of characters before the '&'.
		 */
		before_len = i;
		//assert(i < (int)strlen(string));

		ret = asprintf(&expanded, "%.*s%s%s",
		    before_len, string, key, string + before_len + 1);
		if (ret < 0)
			log_err(1, "asprintf");

		//log_debugx("\"%s\" expanded with key \"%s\" to \"%s\"",
		//    string, key, expanded);

		/*
		 * Figure out where to start searching for next variable.
		 */
		string = expanded;
		i = before_len + strlen(key);
		if (i == (int)strlen(string))
			break;
		backslashed = false;
		//assert(i < (int)strlen(string));
	}

	return (expanded);
}