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
 int LOWERCASE (char const) ; 

__attribute__((used)) static int
CaselessCmp(const char *a, const char *b)
{				/* strcasecmp isn't portable */
    while (*a && *b) {
	int cmp = LOWERCASE(*a) - LOWERCASE(*b);
	if (cmp != 0)
	    break;
	a++, b++;
    }
    return LOWERCASE(*a) - LOWERCASE(*b);
}