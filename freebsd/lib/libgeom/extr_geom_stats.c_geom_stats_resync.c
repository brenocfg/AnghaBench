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
 void* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 void* mmap (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int npages ; 
 int pagesize ; 
 void* statp ; 
 int statsfd ; 

void
geom_stats_resync(void)
{
	void *p;

	if (statsfd == -1)
		return;
	for (;;) {
		p = mmap(statp, (npages + 1) * pagesize,
		    PROT_READ, MAP_SHARED, statsfd, 0);
		if (p == MAP_FAILED)
			break;
		else
			statp = p;
		npages++;
	}
}