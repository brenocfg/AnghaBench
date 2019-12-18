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
struct of_reconfig_data {int /*<<< orphan*/  dn; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  OF_RECONFIG_ATTACH_NODE 129 
#define  OF_RECONFIG_DETACH_NODE 128 
 int notifier_from_errno (int) ; 
 int pseries_add_processor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pseries_remove_processor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pseries_smp_notifier(struct notifier_block *nb,
				unsigned long action, void *data)
{
	struct of_reconfig_data *rd = data;
	int err = 0;

	switch (action) {
	case OF_RECONFIG_ATTACH_NODE:
		err = pseries_add_processor(rd->dn);
		break;
	case OF_RECONFIG_DETACH_NODE:
		pseries_remove_processor(rd->dn);
		break;
	}
	return notifier_from_errno(err);
}