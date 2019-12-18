#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* subsys_data; } ;
struct device {TYPE_2__ power; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_7__ {int /*<<< orphan*/  effective_constraint_ns; } ;
struct TYPE_8__ {TYPE_3__ td; } ;
struct TYPE_5__ {scalar_t__ domain_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PM_QOS_RESUME_LATENCY ; 
 int /*<<< orphan*/  NSEC_PER_USEC ; 
 TYPE_4__* dev_gpd_data (struct device*) ; 
 int /*<<< orphan*/  dev_pm_qos_read_value (struct device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dev_update_qos_constraint(struct device *dev, void *data)
{
	s64 *constraint_ns_p = data;
	s64 constraint_ns;

	if (dev->power.subsys_data && dev->power.subsys_data->domain_data) {
		/*
		 * Only take suspend-time QoS constraints of devices into
		 * account, because constraints updated after the device has
		 * been suspended are not guaranteed to be taken into account
		 * anyway.  In order for them to take effect, the device has to
		 * be resumed and suspended again.
		 */
		constraint_ns = dev_gpd_data(dev)->td.effective_constraint_ns;
	} else {
		/*
		 * The child is not in a domain and there's no info on its
		 * suspend/resume latencies, so assume them to be negligible and
		 * take its current PM QoS constraint (that's the only thing
		 * known at this point anyway).
		 */
		constraint_ns = dev_pm_qos_read_value(dev, DEV_PM_QOS_RESUME_LATENCY);
		constraint_ns *= NSEC_PER_USEC;
	}

	if (constraint_ns < *constraint_ns_p)
		*constraint_ns_p = constraint_ns;

	return 0;
}