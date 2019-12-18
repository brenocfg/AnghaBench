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
struct autr_ta {scalar_t__ fetched; struct autr_ta* next; } ;
struct TYPE_2__ {struct autr_ta* keys; } ;

/* Variables and functions */

__attribute__((used)) static void
init_events(struct trust_anchor* tp)
{
	struct autr_ta* ta;
	for(ta=tp->autr->keys; ta; ta=ta->next) {
		ta->fetched = 0;
	}
}