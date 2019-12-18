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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  rs; int /*<<< orphan*/  rw; } ;

/* Variables and functions */
 int MODE_DATA ; 
 int /*<<< orphan*/  ndelay (int) ; 
 TYPE_1__* picvue ; 
 int /*<<< orphan*/  pvc_reg_read () ; 
 int /*<<< orphan*/  pvc_reg_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvc_wait () ; 
 int /*<<< orphan*/  pvc_write_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pvc_write(u8 byte, int mode)
{
	u32 data = pvc_reg_read();
	data &= ~picvue->rw;
	if (mode == MODE_DATA)
		data |= picvue->rs;
	else
		data &= ~picvue->rs;
	pvc_reg_write(data);
	ndelay(40);
	pvc_write_byte(data, byte);
	if (mode == MODE_DATA)
		data &= ~picvue->rs;
	else
		data |= picvue->rs;
	pvc_reg_write(data);
	pvc_wait();
}