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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int wantedblksize ; 

__attribute__((used)) static int
compare_blk64(uint64_t *wantedblk, uint64_t curblk)
{
    int i;

    for (i = 0; i < wantedblksize; i++) {
	if (wantedblk[i] != 0 && wantedblk[i] == curblk) {
	    wantedblk[i] = 0;
	    return 1;
	}
    }
    return 0;
}