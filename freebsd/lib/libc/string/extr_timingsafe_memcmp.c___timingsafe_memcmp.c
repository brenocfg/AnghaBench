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
 unsigned char const CHAR_BIT ; 

int
__timingsafe_memcmp(const void *b1, const void *b2, size_t len)
{
        const unsigned char *p1 = b1, *p2 = b2;
        size_t i;
        int res = 0, done = 0;

        for (i = 0; i < len; i++) {
                /* lt is -1 if p1[i] < p2[i]; else 0. */
                int lt = (p1[i] - p2[i]) >> CHAR_BIT;

                /* gt is -1 if p1[i] > p2[i]; else 0. */
                int gt = (p2[i] - p1[i]) >> CHAR_BIT;

                /* cmp is 1 if p1[i] > p2[i]; -1 if p1[i] < p2[i]; else 0. */
                int cmp = lt - gt;

                /* set res = cmp if !done. */
                res |= cmp & ~done;

                /* set done if p1[i] != p2[i]. */
                done |= lt | gt;
        }

        return (res);
}