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
struct module_env {int dummy; } ;
struct autr_ta {int s; int /*<<< orphan*/  fetched; int /*<<< orphan*/  revoked; int /*<<< orphan*/  last_change; } ;

/* Variables and functions */
#define  AUTR_STATE_ADDPEND 133 
#define  AUTR_STATE_MISSING 132 
#define  AUTR_STATE_REMOVED 131 
#define  AUTR_STATE_REVOKED 130 
#define  AUTR_STATE_START 129 
#define  AUTR_STATE_VALID 128 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  do_addtime (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  do_keypres (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  do_keyrem (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  do_newkey (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  do_remtime (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  do_revoked (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  log_assert (struct autr_ta*) ; 
 int /*<<< orphan*/  reset_holddown (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  verbose_key (struct autr_ta*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
anchor_state_update(struct module_env* env, struct autr_ta* anchor, int* c)
{
	log_assert(anchor);
	switch(anchor->s) {
	/* START */
	case AUTR_STATE_START:
		/* NewKey: ADDPEND */
		if (anchor->fetched)
			do_newkey(env, anchor, c);
		break;
	/* ADDPEND */
	case AUTR_STATE_ADDPEND:
		/* KeyRem: START */
		if (!anchor->fetched)
			do_keyrem(env, anchor, c);
		/* AddTime: VALID */
		else	do_addtime(env, anchor, c);
		break;
	/* VALID */
	case AUTR_STATE_VALID:
		/* RevBit: REVOKED */
		if (anchor->revoked)
			do_revoked(env, anchor, c);
		/* KeyRem: MISSING */
		else if (!anchor->fetched)
			do_keyrem(env, anchor, c);
		else if(!anchor->last_change) {
			verbose_key(anchor, VERB_ALGO, "first seen");
			reset_holddown(env, anchor, c);
		}
		break;
	/* MISSING */
	case AUTR_STATE_MISSING:
		/* RevBit: REVOKED */
		if (anchor->revoked)
			do_revoked(env, anchor, c);
		/* KeyPres */
		else if (anchor->fetched)
			do_keypres(env, anchor, c);
		break;
	/* REVOKED */
	case AUTR_STATE_REVOKED:
		if (anchor->fetched)
			reset_holddown(env, anchor, c);
		/* RemTime: REMOVED */
		else	do_remtime(env, anchor, c);
		break;
	/* REMOVED */
	case AUTR_STATE_REMOVED:
	default:
		break;
	}
}