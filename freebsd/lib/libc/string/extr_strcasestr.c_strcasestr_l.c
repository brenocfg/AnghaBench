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
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncasecmp_l (char const*,char const*,size_t,int /*<<< orphan*/ ) ; 
 char tolower_l (unsigned char,int /*<<< orphan*/ ) ; 

char *
strcasestr_l(const char *s, const char *find, locale_t locale)
{
	char c, sc;
	size_t len;
	FIX_LOCALE(locale);

	if ((c = *find++) != 0) {
		c = tolower_l((unsigned char)c, locale);
		len = strlen(find);
		do {
			do {
				if ((sc = *s++) == 0)
					return (NULL);
			} while ((char)tolower_l((unsigned char)sc, locale) != c);
		} while (strncasecmp_l(s, find, len, locale) != 0);
		s--;
	}
	return ((char *)s);
}