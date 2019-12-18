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
 char* skip_delay (char const*) ; 

__attribute__((used)) static unsigned
compare_part(const char *part, const char *full)
{
    const char *next_part;
    const char *next_full;
    unsigned used_full = 0;
    unsigned used_delay = 0;

    while (*part != 0) {
	if (*part != *full) {
	    used_full = 0;
	    break;
	}

	/*
	 * Adjust the return-value to allow the rare case of
	 *      string<delay>string
	 * to remove the whole piece.  The most common case is a delay at the
	 * end of the string.  The adjusted string will retain the delay, which
	 * is conservative.
	 */
	if (used_delay != 0) {
	    used_full += used_delay;
	    used_delay = 0;
	}
	if (*part == '$' && *full == '$') {
	    next_part = skip_delay(part);
	    next_full = skip_delay(full);
	    if (next_part != part && next_full != full) {
		used_delay += (unsigned) (next_full - full);
		full = next_full;
		part = next_part;
		continue;
	    }
	}
	++used_full;
	++part;
	++full;
    }
    return used_full;
}