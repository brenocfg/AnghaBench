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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  locale_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_LOCALE (int /*<<< orphan*/ ) ; 
 int tolower_l (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

int
strncasecmp_l(const char *s1, const char *s2, size_t n, locale_t locale)
{
	FIX_LOCALE(locale);
	if (n != 0) {
		const u_char
				*us1 = (const u_char *)s1,
				*us2 = (const u_char *)s2;

		do {
			if (tolower_l(*us1, locale) != tolower_l(*us2++, locale))
				return (tolower_l(*us1, locale) - tolower_l(*--us2, locale));
			if (*us1++ == '\0')
				break;
		} while (--n != 0);
	}
	return (0);
}