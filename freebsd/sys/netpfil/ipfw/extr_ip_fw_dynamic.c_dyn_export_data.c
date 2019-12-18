#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct dyn_data {int flags; int /*<<< orphan*/  hashval; int /*<<< orphan*/  ack_rev; int /*<<< orphan*/  ack_fwd; int /*<<< orphan*/  state; int /*<<< orphan*/  rulenum; scalar_t__ expire; scalar_t__ bcnt_rev; scalar_t__ bcnt_fwd; scalar_t__ pcnt_rev; scalar_t__ pcnt_fwd; } ;
typedef  int /*<<< orphan*/  set ;
struct TYPE_3__ {char rule; struct TYPE_3__* next; int /*<<< orphan*/  bucket; scalar_t__ count; int /*<<< orphan*/  ack_rev; int /*<<< orphan*/  ack_fwd; int /*<<< orphan*/ * parent; int /*<<< orphan*/  state; scalar_t__ expire; scalar_t__ bcnt; scalar_t__ pcnt; int /*<<< orphan*/  kidx; int /*<<< orphan*/  dyn_type; } ;
typedef  TYPE_1__ ipfw_dyn_rule ;

/* Variables and functions */
 int DYN_REFERENCED ; 
 int /*<<< orphan*/  IPFW_DYN_ORPHANED ; 
 scalar_t__ TIME_LEQ (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
dyn_export_data(const struct dyn_data *data, uint16_t kidx, uint8_t type,
    uint8_t set, ipfw_dyn_rule *dst)
{

	dst->dyn_type = type;
	dst->kidx = kidx;
	dst->pcnt = data->pcnt_fwd + data->pcnt_rev;
	dst->bcnt = data->bcnt_fwd + data->bcnt_rev;
	dst->expire = TIME_LEQ(data->expire, time_uptime) ?  0:
	    data->expire - time_uptime;

	/* 'rule' is used to pass up the rule number and set */
	memcpy(&dst->rule, &data->rulenum, sizeof(data->rulenum));

	/* store set number into high word of dst->rule pointer. */
	memcpy((char *)&dst->rule + sizeof(data->rulenum), &set, sizeof(set));

	dst->state = data->state;
	if (data->flags & DYN_REFERENCED)
		dst->state |= IPFW_DYN_ORPHANED;

	/* unused fields */
	dst->parent = NULL;
	dst->ack_fwd = data->ack_fwd;
	dst->ack_rev = data->ack_rev;
	dst->count = 0;
	dst->bucket = data->hashval;
	/*
	 * The legacy userland code will interpret a NULL here as a marker
	 * for the last dynamic rule.
	 */
	dst->next = (ipfw_dyn_rule *)1;
}