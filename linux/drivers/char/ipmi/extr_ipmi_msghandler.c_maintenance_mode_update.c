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
struct ipmi_smi {int /*<<< orphan*/  maintenance_mode_enable; int /*<<< orphan*/  send_info; TYPE_1__* handlers; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_maintenance_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void maintenance_mode_update(struct ipmi_smi *intf)
{
	if (intf->handlers->set_maintenance_mode)
		intf->handlers->set_maintenance_mode(
			intf->send_info, intf->maintenance_mode_enable);
}