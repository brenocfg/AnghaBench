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
struct rt_spare {int dummy; } ;
struct rt_entry {struct rt_spare* rt_spares; } ;

/* Variables and functions */
 scalar_t__ BETTER_LINK (struct rt_entry*,struct rt_spare*,struct rt_spare*) ; 
 int NUM_SPARES ; 

__attribute__((used)) static struct rt_spare *
rts_better(struct rt_entry *rt)
{
	struct rt_spare *rts, *rts1;
	int i;

	/* find the best alternative among the spares */
	rts = rt->rt_spares+1;
	for (i = NUM_SPARES, rts1 = rts+1; i > 2; i--, rts1++) {
		if (BETTER_LINK(rt,rts1,rts))
			rts = rts1;
	}

	return rts;
}