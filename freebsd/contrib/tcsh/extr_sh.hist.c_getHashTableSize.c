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
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static unsigned
getHashTableSize(int hlen)
{
    unsigned target = hlen * 2;
    unsigned e = 5;
    unsigned size;
    while ((size = 1<<e) < target)
	e++;
#ifdef PRIME_LENGTH			/* need good HTL */
    /* Not all prime, but most are and none have factors smaller than 11. */
    return size+15;
#else
    assert((size & (size-1)) == 0);	/* must be a power of two */
    return size;
#endif
}