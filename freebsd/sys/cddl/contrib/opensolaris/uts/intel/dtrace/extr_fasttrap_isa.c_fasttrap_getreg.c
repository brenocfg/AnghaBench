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
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int uint_t ;
struct reg {int /*<<< orphan*/  r_gs; int /*<<< orphan*/  r_es; int /*<<< orphan*/  r_ds; int /*<<< orphan*/  r_fs; int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_rsp; int /*<<< orphan*/  r_rflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_rip; int /*<<< orphan*/  r_err; int /*<<< orphan*/  r_trapno; int /*<<< orphan*/  r_rax; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_rdx; int /*<<< orphan*/  r_rbx; int /*<<< orphan*/  r_rbp; int /*<<< orphan*/  r_rsi; int /*<<< orphan*/  r_rdi; int /*<<< orphan*/  r_r8; int /*<<< orphan*/  r_r9; int /*<<< orphan*/  r_r10; int /*<<< orphan*/  r_r11; int /*<<< orphan*/  r_r12; int /*<<< orphan*/  r_r13; int /*<<< orphan*/  r_r14; int /*<<< orphan*/  r_r15; } ;
typedef  int /*<<< orphan*/  greg_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_FSBASE ; 
 int /*<<< orphan*/  MSR_GSBASE ; 
#define  REG_CS 155 
#define  REG_DS 154 
#define  REG_ERR 153 
#define  REG_ES 152 
#define  REG_FS 151 
#define  REG_FSBASE 150 
#define  REG_GS 149 
#define  REG_GSBASE 148 
#define  REG_R10 147 
#define  REG_R11 146 
#define  REG_R12 145 
#define  REG_R13 144 
#define  REG_R14 143 
#define  REG_R15 142 
#define  REG_R8 141 
#define  REG_R9 140 
#define  REG_RAX 139 
#define  REG_RBP 138 
#define  REG_RBX 137 
#define  REG_RCX 136 
#define  REG_RDI 135 
#define  REG_RDX 134 
#define  REG_RFL 133 
#define  REG_RIP 132 
#define  REG_RSI 131 
#define  REG_RSP 130 
#define  REG_SS 129 
#define  REG_TRAPNO 128 
 int _NGREG ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ulong_t
fasttrap_getreg(struct reg *rp, uint_t reg)
{
#ifdef __amd64
	switch (reg) {
	case REG_R15:		return (rp->r_r15);
	case REG_R14:		return (rp->r_r14);
	case REG_R13:		return (rp->r_r13);
	case REG_R12:		return (rp->r_r12);
	case REG_R11:		return (rp->r_r11);
	case REG_R10:		return (rp->r_r10);
	case REG_R9:		return (rp->r_r9);
	case REG_R8:		return (rp->r_r8);
	case REG_RDI:		return (rp->r_rdi);
	case REG_RSI:		return (rp->r_rsi);
	case REG_RBP:		return (rp->r_rbp);
	case REG_RBX:		return (rp->r_rbx);
	case REG_RDX:		return (rp->r_rdx);
	case REG_RCX:		return (rp->r_rcx);
	case REG_RAX:		return (rp->r_rax);
	case REG_TRAPNO:	return (rp->r_trapno);
	case REG_ERR:		return (rp->r_err);
	case REG_RIP:		return (rp->r_rip);
	case REG_CS:		return (rp->r_cs);
	case REG_RFL:		return (rp->r_rflags);
	case REG_RSP:		return (rp->r_rsp);
	case REG_SS:		return (rp->r_ss);
	case REG_FS:		return (rp->r_fs);
	case REG_GS:		return (rp->r_gs);
	case REG_DS:		return (rp->r_ds);
	case REG_ES:		return (rp->r_es);
	case REG_FSBASE:	return (rdmsr(MSR_FSBASE));
	case REG_GSBASE:	return (rdmsr(MSR_GSBASE));
	}

	panic("dtrace: illegal register constant");
	/*NOTREACHED*/
#else
#define _NGREG 19
	if (reg >= _NGREG)
		panic("dtrace: illegal register constant");

	return (((greg_t *)&rp->r_gs)[reg]);
#endif
}