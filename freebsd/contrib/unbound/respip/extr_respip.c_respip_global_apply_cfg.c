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
struct respip_set {int dummy; } ;
struct config_file {int /*<<< orphan*/ * respip_tags; int /*<<< orphan*/ * respip_actions; int /*<<< orphan*/ * respip_data; int /*<<< orphan*/  num_tags; int /*<<< orphan*/  tagname; } ;

/* Variables and functions */
 int respip_set_apply_cfg (struct respip_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
respip_global_apply_cfg(struct respip_set* set, struct config_file* cfg)
{
	int ret = respip_set_apply_cfg(set, cfg->tagname, cfg->num_tags,
		cfg->respip_tags, cfg->respip_actions, cfg->respip_data);
	cfg->respip_data = NULL;
	cfg->respip_actions = NULL;
	cfg->respip_tags = NULL;
	return ret;
}