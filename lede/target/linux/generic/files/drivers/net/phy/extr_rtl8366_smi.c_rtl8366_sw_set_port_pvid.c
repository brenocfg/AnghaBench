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
struct switch_dev {int dummy; } ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int rtl8366_set_pvid (struct rtl8366_smi*,int,int) ; 
 struct rtl8366_smi* sw_to_rtl8366_smi (struct switch_dev*) ; 

int rtl8366_sw_set_port_pvid(struct switch_dev *dev, int port, int val)
{
	struct rtl8366_smi *smi = sw_to_rtl8366_smi(dev);
	return rtl8366_set_pvid(smi, port, val);
}