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
typedef  int u16 ;
struct sh_fpu_soft_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int id_fnmx (struct sh_fpu_soft_struct*,struct pt_regs*,int) ; 
 int id_sys (struct sh_fpu_soft_struct*,struct pt_regs*,int) ; 

__attribute__((used)) static int fpu_emulate(u16 code, struct sh_fpu_soft_struct *fregs, struct pt_regs *regs)
{
	if ((code & 0xf000) == 0xf000)
		return id_fnmx(fregs, regs, code);
	else
		return id_sys(fregs, regs, code);
}