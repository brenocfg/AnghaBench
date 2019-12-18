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
typedef  int /*<<< orphan*/  u8 ;
struct pci_slot {TYPE_1__* hotplug; } ;
struct pci_dev {scalar_t__ error_state; struct pci_slot* slot; } ;
struct hotplug_slot_ops {int (* get_adapter_status ) (TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* set_attention_status ) (TYPE_1__*,int) ;} ;
struct TYPE_3__ {struct hotplug_slot_ops* ops; } ;

/* Variables and functions */
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool eeh_slot_presence_check(struct pci_dev *pdev)
{
	const struct hotplug_slot_ops *ops;
	struct pci_slot *slot;
	u8 state;
	int rc;

	if (!pdev)
		return false;

	if (pdev->error_state == pci_channel_io_perm_failure)
		return false;

	slot = pdev->slot;
	if (!slot || !slot->hotplug)
		return true;

	ops = slot->hotplug->ops;
	if (!ops || !ops->get_adapter_status)
		return true;

	/* set the attention indicator while we've got the slot ops */
	if (ops->set_attention_status)
		ops->set_attention_status(slot->hotplug, 1);

	rc = ops->get_adapter_status(slot->hotplug, &state);
	if (rc)
		return true;

	return !!state;
}