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
 size_t bcache_blksize ; 
 size_t bcache_total_nblks ; 

void
bcache_init(size_t nblks, size_t bsize)
{
    /* set up control data */
    bcache_total_nblks = nblks;
    bcache_blksize = bsize;
}