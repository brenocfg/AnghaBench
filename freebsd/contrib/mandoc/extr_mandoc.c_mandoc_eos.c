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
 int /*<<< orphan*/  isalnum (unsigned char) ; 

int
mandoc_eos(const char *p, size_t sz)
{
	const char	*q;
	int		 enclosed, found;

	if (0 == sz)
		return 0;

	/*
	 * End-of-sentence recognition must include situations where
	 * some symbols, such as `)', allow prior EOS punctuation to
	 * propagate outward.
	 */

	enclosed = found = 0;
	for (q = p + (int)sz - 1; q >= p; q--) {
		switch (*q) {
		case '\"':
		case '\'':
		case ']':
		case ')':
			if (0 == found)
				enclosed = 1;
			break;
		case '.':
		case '!':
		case '?':
			found = 1;
			break;
		default:
			return found &&
			    (!enclosed || isalnum((unsigned char)*q));
		}
	}

	return found && !enclosed;
}