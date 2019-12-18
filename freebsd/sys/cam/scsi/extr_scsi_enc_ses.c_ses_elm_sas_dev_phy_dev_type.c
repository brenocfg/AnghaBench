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
struct ses_elm_sas_device_phy {int byte0; } ;

/* Variables and functions */

int
ses_elm_sas_dev_phy_dev_type(struct ses_elm_sas_device_phy *phy)
{
	return (((phy)->byte0 >> 4) & 0x7);
}