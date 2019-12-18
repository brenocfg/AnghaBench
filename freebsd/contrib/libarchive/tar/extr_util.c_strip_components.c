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
strip_components(const char *p, int elements)
{
	/* Skip as many elements as necessary. */
	while (elements > 0) {
		switch (*p++) {
		case '/':
#if defined(_WIN32) && !defined(__CYGWIN__)
		case '\\': /* Support \ path sep on Windows ONLY. */
#endif
			elements--;
			break;
		case '\0':
			/* Path is too short, skip it. */
			return (NULL);
		}
	}

	/* Skip any / characters.  This handles short paths that have
	 * additional / termination.  This also handles the case where
	 * the logic above stops in the middle of a duplicate //
	 * sequence (which would otherwise get converted to an
	 * absolute path). */
	for (;;) {
		switch (*p) {
		case '/':
#if defined(_WIN32) && !defined(__CYGWIN__)
		case '\\': /* Support \ path sep on Windows ONLY. */
#endif
			++p;
			break;
		case '\0':
			return (NULL);
		default:
			return (p);
		}
	}
}