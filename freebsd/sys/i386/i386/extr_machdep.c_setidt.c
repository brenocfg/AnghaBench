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
typedef  int /*<<< orphan*/  inthand_t ;

/* Variables and functions */
 uintptr_t setidt_disp ; 
 int /*<<< orphan*/  setidt_nodisp (int,uintptr_t,int,int,int) ; 

void
setidt(int idx, inthand_t *func, int typ, int dpl, int selec)
{
	uintptr_t off;

	off = func != NULL ? (uintptr_t)func + setidt_disp : 0;
	setidt_nodisp(idx, off, typ, dpl, selec);
}