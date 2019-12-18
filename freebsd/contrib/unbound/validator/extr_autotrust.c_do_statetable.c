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
struct module_env {int dummy; } ;
struct autr_ta {struct autr_ta* next; } ;
struct TYPE_2__ {struct autr_ta* keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  anchor_state_update (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  remove_missing_trustanchors (struct module_env*,struct trust_anchor*,int*) ; 
 int /*<<< orphan*/  ta_is_dnskey_sep (struct autr_ta*) ; 

__attribute__((used)) static int
do_statetable(struct module_env* env, struct trust_anchor* tp, int* changed)
{
	struct autr_ta* anchor;
	for(anchor = tp->autr->keys; anchor; anchor = anchor->next) {
		/* Only do KSKs */
		if(!ta_is_dnskey_sep(anchor))
			continue;
		anchor_state_update(env, anchor, changed);
	}
	remove_missing_trustanchors(env, tp, changed);
	return 1;
}