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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int e; int data_mask; int data_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndelay (int) ; 
 TYPE_1__* picvue ; 
 int /*<<< orphan*/  pvc_reg_write (int) ; 

__attribute__((used)) static void pvc_write_byte(u32 data, u8 byte)
{
	data |= picvue->e;
	pvc_reg_write(data);
	data &= ~picvue->data_mask;
	data |= byte << picvue->data_shift;
	pvc_reg_write(data);
	ndelay(220);
	pvc_reg_write(data & ~picvue->e);
	ndelay(220);
}