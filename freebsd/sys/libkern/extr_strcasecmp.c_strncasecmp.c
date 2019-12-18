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

/* Variables and functions */
 int tolower (int /*<<< orphan*/  const) ; 

int
strncasecmp(const char *s1, const char *s2, size_t n)
{

	if (n != 0) {
		const u_char *us1 = (const u_char *)s1;
		const u_char *us2 = (const u_char *)s2;

		do {
			if (tolower(*us1) != tolower(*us2))
				return (tolower(*us1) - tolower(*us2));
			if (*us1++ == '\0')
				break;
			us2++;
		} while (--n != 0);
	}
	return (0);
}