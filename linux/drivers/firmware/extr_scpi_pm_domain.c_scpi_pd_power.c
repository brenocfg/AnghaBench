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
struct scpi_pm_domain {int /*<<< orphan*/  domain; TYPE_1__* ops; } ;
typedef  enum scpi_power_domain_state { ____Placeholder_scpi_power_domain_state } scpi_power_domain_state ;
struct TYPE_2__ {int (* device_set_power_state ) (int /*<<< orphan*/ ,int) ;int (* device_get_power_state ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int SCPI_PD_STATE_OFF ; 
 int SCPI_PD_STATE_ON ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scpi_pd_power(struct scpi_pm_domain *pd, bool power_on)
{
	int ret;
	enum scpi_power_domain_state state;

	if (power_on)
		state = SCPI_PD_STATE_ON;
	else
		state = SCPI_PD_STATE_OFF;

	ret = pd->ops->device_set_power_state(pd->domain, state);
	if (ret)
		return ret;

	return !(state == pd->ops->device_get_power_state(pd->domain));
}