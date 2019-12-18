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
struct blkcg_policy_data {int dummy; } ;
struct ioc_cgrp {struct blkcg_policy_data cpd; int /*<<< orphan*/  dfl_weight; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_WEIGHT_DFL ; 
 struct ioc_cgrp* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct blkcg_policy_data *ioc_cpd_alloc(gfp_t gfp)
{
	struct ioc_cgrp *iocc;

	iocc = kzalloc(sizeof(struct ioc_cgrp), gfp);
	if (!iocc)
		return NULL;

	iocc->dfl_weight = CGROUP_WEIGHT_DFL;
	return &iocc->cpd;
}