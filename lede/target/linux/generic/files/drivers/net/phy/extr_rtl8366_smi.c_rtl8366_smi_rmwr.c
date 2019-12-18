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
typedef  int u32 ;
struct rtl8366_smi {int dummy; } ;

/* Variables and functions */
 int rtl8366_smi_read_reg (struct rtl8366_smi*,int,int*) ; 
 int rtl8366_smi_write_reg (struct rtl8366_smi*,int,int) ; 

int rtl8366_smi_rmwr(struct rtl8366_smi *smi, u32 addr, u32 mask, u32 data)
{
	u32 t;
	int err;

	err = rtl8366_smi_read_reg(smi, addr, &t);
	if (err)
		return err;

	err = rtl8366_smi_write_reg(smi, addr, (t & ~mask) | data);
	return err;

}