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

/* Variables and functions */
 int /*<<< orphan*/  __rtl8366_smi_cleanup (struct rtl8366_smi*) ; 
 int /*<<< orphan*/  rtl8366_debugfs_remove (struct rtl8366_smi*) ; 
 int /*<<< orphan*/  rtl8366_smi_mii_cleanup (struct rtl8366_smi*) ; 

void rtl8366_smi_cleanup(struct rtl8366_smi *smi)
{
	rtl8366_debugfs_remove(smi);
	rtl8366_smi_mii_cleanup(smi);
	__rtl8366_smi_cleanup(smi);
}