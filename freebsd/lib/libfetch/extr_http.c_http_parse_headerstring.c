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

__attribute__((used)) static const char *
http_parse_headerstring(const char *cp, char *obuf)
{
	for (;;) {
		switch (*cp) {
		case 0: /* Unterminated string */
			*obuf = 0;
			return (NULL);
		case '"': /* Ending quote */
			*obuf = 0;
			return (++cp);
		case '\\':
			if (*++cp == 0) {
				*obuf = 0;
				return (NULL);
			}
			/* FALLTHROUGH */
		default:
			*obuf++ = *cp++;
		}
	}
}