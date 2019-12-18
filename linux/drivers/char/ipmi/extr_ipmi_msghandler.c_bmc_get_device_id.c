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
struct ipmi_smi {int dummy; } ;
struct ipmi_device_id {int dummy; } ;
struct bmc_device {int dummy; } ;
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 int __bmc_get_device_id (struct ipmi_smi*,struct bmc_device*,struct ipmi_device_id*,int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int bmc_get_device_id(struct ipmi_smi *intf, struct bmc_device *bmc,
			     struct ipmi_device_id *id,
			     bool *guid_set, guid_t *guid)
{
	return __bmc_get_device_id(intf, bmc, id, guid_set, guid, -1);
}