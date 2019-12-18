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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct ipmi_smi_powernv {int /*<<< orphan*/  irq; int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 struct ipmi_smi_powernv* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ipmi_smi_powernv*) ; 
 int /*<<< orphan*/  ipmi_unregister_smi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipmi_powernv_remove(struct platform_device *pdev)
{
	struct ipmi_smi_powernv *smi = dev_get_drvdata(&pdev->dev);

	ipmi_unregister_smi(smi->intf);
	free_irq(smi->irq, smi);
	irq_dispose_mapping(smi->irq);

	return 0;
}