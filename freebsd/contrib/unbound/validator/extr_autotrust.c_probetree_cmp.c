#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trust_anchor {TYPE_1__* autr; } ;
struct TYPE_2__ {scalar_t__ next_probe_time; } ;

/* Variables and functions */
 int anchor_cmp (void const*,void const*) ; 
 int /*<<< orphan*/  log_assert (int) ; 

int probetree_cmp(const void* x, const void* y)
{
	struct trust_anchor* a = (struct trust_anchor*)x;
	struct trust_anchor* b = (struct trust_anchor*)y;
	log_assert(a->autr && b->autr);
	if(a->autr->next_probe_time < b->autr->next_probe_time)
		return -1;
	if(a->autr->next_probe_time > b->autr->next_probe_time)
		return 1;
	/* time is equal, sort on trust point identity */
	return anchor_cmp(x, y);
}