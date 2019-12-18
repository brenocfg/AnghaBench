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
 scalar_t__ bmember_isset_bit (void const*,unsigned int,size_t) ; 

__attribute__((used)) static void
bmember_put_bit(unsigned char *p, const void *data, unsigned int bit,
		size_t size, unsigned int *bitset)
{
    unsigned int localbit = bit % 8;

    if (bmember_isset_bit(data, bit, size)) {
	*p |= (1 << (7 - localbit));
	if (*bitset == 0)
	    *bitset = (7 - localbit) + 1;
    }
}