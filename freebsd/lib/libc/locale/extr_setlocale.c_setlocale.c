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
 int EINVAL ; 
 int ENCODING_LEN ; 
 int LC_ALL ; 
 int _LC_LAST ; 
 char* __get_locale_env (int) ; 
 char** current_categories ; 
 char* currentlocale () ; 
 int errno ; 
 char* loadlocale (int) ; 
 char** new_categories ; 
 char** saved_categories ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int strlen (char const*) ; 

char *
setlocale(int category, const char *locale)
{
	int i, j, len, saverr;
	const char *env, *r;

	if (category < LC_ALL || category >= _LC_LAST) {
		errno = EINVAL;
		return (NULL);
	}
	if (locale == NULL)
		return (category != LC_ALL ?
		    current_categories[category] : currentlocale());

	/*
	 * Default to the current locale for everything.
	 */
	for (i = 1; i < _LC_LAST; ++i)
		(void)strcpy(new_categories[i], current_categories[i]);

	/*
	 * Now go fill up new_categories from the locale argument
	 */
	if (!*locale) {
		if (category == LC_ALL) {
			for (i = 1; i < _LC_LAST; ++i) {
				env = __get_locale_env(i);
				if (strlen(env) > ENCODING_LEN) {
					errno = EINVAL;
					return (NULL);
				}
				(void)strcpy(new_categories[i], env);
			}
		} else {
			env = __get_locale_env(category);
			if (strlen(env) > ENCODING_LEN) {
				errno = EINVAL;
				return (NULL);
			}
			(void)strcpy(new_categories[category], env);
		}
	} else if (category != LC_ALL) {
		if (strlen(locale) > ENCODING_LEN) {
			errno = EINVAL;
			return (NULL);
		}
		(void)strcpy(new_categories[category], locale);
	} else {
		if ((r = strchr(locale, '/')) == NULL) {
			if (strlen(locale) > ENCODING_LEN) {
				errno = EINVAL;
				return (NULL);
			}
			for (i = 1; i < _LC_LAST; ++i)
				(void)strcpy(new_categories[i], locale);
		} else {
			for (i = 1; r[1] == '/'; ++r)
				;
			if (!r[1]) {
				errno = EINVAL;
				return (NULL);	/* Hmm, just slashes... */
			}
			do {
				if (i == _LC_LAST)
					break;	/* Too many slashes... */
				if ((len = r - locale) > ENCODING_LEN) {
					errno = EINVAL;
					return (NULL);
				}
				(void)strlcpy(new_categories[i], locale,
				    len + 1);
				i++;
				while (*r == '/')
					r++;
				locale = r;
				while (*r && *r != '/')
					r++;
			} while (*locale);
			while (i < _LC_LAST) {
				(void)strcpy(new_categories[i],
				    new_categories[i - 1]);
				i++;
			}
		}
	}

	if (category != LC_ALL)
		return (loadlocale(category));

	for (i = 1; i < _LC_LAST; ++i) {
		(void)strcpy(saved_categories[i], current_categories[i]);
		if (loadlocale(i) == NULL) {
			saverr = errno;
			for (j = 1; j < i; j++) {
				(void)strcpy(new_categories[j],
				    saved_categories[j]);
				if (loadlocale(j) == NULL) {
					(void)strcpy(new_categories[j], "C");
					(void)loadlocale(j);
				}
			}
			errno = saverr;
			return (NULL);
		}
	}
	return (currentlocale());
}