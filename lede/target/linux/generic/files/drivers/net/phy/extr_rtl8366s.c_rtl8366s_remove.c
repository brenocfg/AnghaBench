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
struct rtl8366_smi {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct rtl8366_smi*) ; 
 struct rtl8366_smi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8366_smi_cleanup (struct rtl8366_smi*) ; 
 int /*<<< orphan*/  rtl8366s_switch_cleanup (struct rtl8366_smi*) ; 

__attribute__((used)) static int rtl8366s_remove(struct platform_device *pdev)
{
	struct rtl8366_smi *smi = platform_get_drvdata(pdev);

	if (smi) {
		rtl8366s_switch_cleanup(smi);
		platform_set_drvdata(pdev, NULL);
		rtl8366_smi_cleanup(smi);
		kfree(smi);
	}

	return 0;
}