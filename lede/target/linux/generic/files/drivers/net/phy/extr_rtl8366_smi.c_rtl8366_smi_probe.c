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
struct rtl8366_smi {int dummy; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 struct rtl8366_smi* ERR_PTR (int) ; 
 int /*<<< orphan*/  kfree (struct rtl8366_smi*) ; 
 struct rtl8366_smi* rtl8366_smi_alloc (TYPE_1__*) ; 
 int rtl8366_smi_probe_of (struct platform_device*,struct rtl8366_smi*) ; 
 int rtl8366_smi_probe_plat (struct platform_device*,struct rtl8366_smi*) ; 

struct rtl8366_smi *rtl8366_smi_probe(struct platform_device *pdev)
{
	struct rtl8366_smi *smi;
	int err;

	smi = rtl8366_smi_alloc(&pdev->dev);
	if (!smi)
		return NULL;

	if (pdev->dev.of_node)
		err = rtl8366_smi_probe_of(pdev, smi);
	else
		err = rtl8366_smi_probe_plat(pdev, smi);

	if (err)
		goto free_smi;

	return smi;

free_smi:
	kfree(smi);
	return ERR_PTR(err);
}