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
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {int scope_mask; int /*<<< orphan*/  FlowLabel; int /*<<< orphan*/  TClass; int /*<<< orphan*/  Q_Key; scalar_t__ sl; scalar_t__ mtu; scalar_t__ rate; } ;
struct precreate_mgroup {int /*<<< orphan*/  mgid; TYPE_1__ flags; } ;
struct part_conf {int /*<<< orphan*/  p_prtn; int /*<<< orphan*/  p_subn; int /*<<< orphan*/  p_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  osm_prtn_add_mcgroup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __create_mgrp(struct part_conf *conf, struct precreate_mgroup *group)
{
	unsigned int scope;

	if (!group->flags.scope_mask) {
		osm_prtn_add_mcgroup(conf->p_log, conf->p_subn, conf->p_prtn,
				     (uint8_t) group->flags.rate,
				     (uint8_t) group->flags.mtu,
				     group->flags.sl,
				     0,
				     group->flags.Q_Key,
				     group->flags.TClass,
				     group->flags.FlowLabel,
				     &group->mgid);
	} else {
		for (scope = 0; scope < 16; scope++) {
			if (((1<<scope) & group->flags.scope_mask) == 0)
				continue;

			osm_prtn_add_mcgroup(conf->p_log, conf->p_subn, conf->p_prtn,
					     (uint8_t)group->flags.rate,
					     (uint8_t)group->flags.mtu,
					     (uint8_t)group->flags.sl,
					     (uint8_t)scope,
					     group->flags.Q_Key,
					     group->flags.TClass,
					     group->flags.FlowLabel,
					     &group->mgid);
		}
	}
}