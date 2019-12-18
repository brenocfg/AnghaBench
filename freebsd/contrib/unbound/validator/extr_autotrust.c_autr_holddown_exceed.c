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
struct autr_ta {scalar_t__ s; struct autr_ta* next; } ;
struct TYPE_2__ {struct autr_ta* keys; } ;

/* Variables and functions */
 scalar_t__ AUTR_STATE_ADDPEND ; 
 int /*<<< orphan*/  do_addtime (struct module_env*,struct autr_ta*,int*) ; 
 scalar_t__ ta_is_dnskey_sep (struct autr_ta*) ; 

__attribute__((used)) static void
autr_holddown_exceed(struct module_env* env, struct trust_anchor* tp, int* c)
{
	struct autr_ta* anchor;
	for(anchor = tp->autr->keys; anchor; anchor = anchor->next) {
		if(ta_is_dnskey_sep(anchor) && 
			anchor->s == AUTR_STATE_ADDPEND)
			do_addtime(env, anchor, c);
	}
}