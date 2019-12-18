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
typedef  scalar_t__ u32 ;
struct scmi_power_ops {int (* state_set ) (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ;int (* state_get ) (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ;} ;
struct scmi_pm_domain {int /*<<< orphan*/  domain; TYPE_1__* handle; } ;
struct generic_pm_domain {int dummy; } ;
struct TYPE_3__ {struct scmi_power_ops* power_ops; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ SCMI_POWER_STATE_GENERIC_OFF ; 
 scalar_t__ SCMI_POWER_STATE_GENERIC_ON ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct scmi_pm_domain* to_scmi_pd (struct generic_pm_domain*) ; 

__attribute__((used)) static int scmi_pd_power(struct generic_pm_domain *domain, bool power_on)
{
	int ret;
	u32 state, ret_state;
	struct scmi_pm_domain *pd = to_scmi_pd(domain);
	const struct scmi_power_ops *ops = pd->handle->power_ops;

	if (power_on)
		state = SCMI_POWER_STATE_GENERIC_ON;
	else
		state = SCMI_POWER_STATE_GENERIC_OFF;

	ret = ops->state_set(pd->handle, pd->domain, state);
	if (!ret)
		ret = ops->state_get(pd->handle, pd->domain, &ret_state);
	if (!ret && state != ret_state)
		return -EIO;

	return ret;
}