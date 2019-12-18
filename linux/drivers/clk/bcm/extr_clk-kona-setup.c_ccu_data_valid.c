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
struct ccu_policy {int dummy; } ;
struct ccu_data {int /*<<< orphan*/  name; struct ccu_policy policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccu_data_offsets_valid (struct ccu_data*) ; 
 scalar_t__ ccu_policy_exists (struct ccu_policy*) ; 
 int /*<<< orphan*/  ccu_policy_valid (struct ccu_policy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ccu_data_valid(struct ccu_data *ccu)
{
	struct ccu_policy *ccu_policy;

	if (!ccu_data_offsets_valid(ccu))
		return false;

	ccu_policy = &ccu->policy;
	if (ccu_policy_exists(ccu_policy))
		if (!ccu_policy_valid(ccu_policy, ccu->name))
			return false;

	return true;
}