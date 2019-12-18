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
 unsigned int HIGH_BITS ; 
 unsigned int SEVENTYFIVE ; 
 unsigned int TWELVE ; 

unsigned
hashjpw(const char *ss)
{				/* another hash function */
    unsigned h = 0;
    unsigned g;
    const unsigned char *s = (const unsigned char *)ss;

    for (; *s; ++s) {
	h = (h << TWELVE) + *s;
	if ((g = h & HIGH_BITS))
	    h = (h ^ (g >> SEVENTYFIVE)) & ~HIGH_BITS;
    }
    return h;
}