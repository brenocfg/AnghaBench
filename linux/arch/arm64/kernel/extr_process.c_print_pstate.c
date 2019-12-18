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
typedef  int u64 ;
struct pt_regs {int pstate; } ;

/* Variables and functions */
 int PSR_AA32_A_BIT ; 
 int PSR_AA32_C_BIT ; 
 int PSR_AA32_E_BIT ; 
 int PSR_AA32_F_BIT ; 
 int PSR_AA32_I_BIT ; 
 int PSR_AA32_N_BIT ; 
 int PSR_AA32_Q_BIT ; 
 int PSR_AA32_T_BIT ; 
 int PSR_AA32_V_BIT ; 
 int PSR_AA32_Z_BIT ; 
 int PSR_A_BIT ; 
 int PSR_C_BIT ; 
 int PSR_D_BIT ; 
 int PSR_F_BIT ; 
 int PSR_I_BIT ; 
 int PSR_N_BIT ; 
 int PSR_PAN_BIT ; 
 int PSR_UAO_BIT ; 
 int PSR_V_BIT ; 
 int PSR_Z_BIT ; 
 scalar_t__ compat_user_mode (struct pt_regs*) ; 
 int /*<<< orphan*/  printk (char*,int,char,char,char,char,char,...) ; 

__attribute__((used)) static void print_pstate(struct pt_regs *regs)
{
	u64 pstate = regs->pstate;

	if (compat_user_mode(regs)) {
		printk("pstate: %08llx (%c%c%c%c %c %s %s %c%c%c)\n",
			pstate,
			pstate & PSR_AA32_N_BIT ? 'N' : 'n',
			pstate & PSR_AA32_Z_BIT ? 'Z' : 'z',
			pstate & PSR_AA32_C_BIT ? 'C' : 'c',
			pstate & PSR_AA32_V_BIT ? 'V' : 'v',
			pstate & PSR_AA32_Q_BIT ? 'Q' : 'q',
			pstate & PSR_AA32_T_BIT ? "T32" : "A32",
			pstate & PSR_AA32_E_BIT ? "BE" : "LE",
			pstate & PSR_AA32_A_BIT ? 'A' : 'a',
			pstate & PSR_AA32_I_BIT ? 'I' : 'i',
			pstate & PSR_AA32_F_BIT ? 'F' : 'f');
	} else {
		printk("pstate: %08llx (%c%c%c%c %c%c%c%c %cPAN %cUAO)\n",
			pstate,
			pstate & PSR_N_BIT ? 'N' : 'n',
			pstate & PSR_Z_BIT ? 'Z' : 'z',
			pstate & PSR_C_BIT ? 'C' : 'c',
			pstate & PSR_V_BIT ? 'V' : 'v',
			pstate & PSR_D_BIT ? 'D' : 'd',
			pstate & PSR_A_BIT ? 'A' : 'a',
			pstate & PSR_I_BIT ? 'I' : 'i',
			pstate & PSR_F_BIT ? 'F' : 'f',
			pstate & PSR_PAN_BIT ? '+' : '-',
			pstate & PSR_UAO_BIT ? '+' : '-');
	}
}