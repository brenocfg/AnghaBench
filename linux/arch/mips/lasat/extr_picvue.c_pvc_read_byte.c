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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int data_mask; int data_shift; int /*<<< orphan*/  e; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndelay (int) ; 
 TYPE_1__* picvue ; 
 int pvc_reg_read () ; 
 int /*<<< orphan*/  pvc_reg_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 pvc_read_byte(u32 data)
{
	u8 byte;

	data |= picvue->e;
	pvc_reg_write(data);
	ndelay(220);
	byte = (pvc_reg_read() & picvue->data_mask) >> picvue->data_shift;
	data &= ~picvue->e;
	pvc_reg_write(data);
	ndelay(220);
	return byte;
}