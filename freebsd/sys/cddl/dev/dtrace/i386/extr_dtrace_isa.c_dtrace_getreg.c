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
typedef  int /*<<< orphan*/  ulong_t ;
typedef  int uint_t ;
struct trapframe {int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_esp; int /*<<< orphan*/  tf_eflags; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_eip; int /*<<< orphan*/  tf_err; int /*<<< orphan*/  tf_trapno; int /*<<< orphan*/  tf_eax; int /*<<< orphan*/  tf_ecx; int /*<<< orphan*/  tf_ebx; int /*<<< orphan*/  tf_isp; int /*<<< orphan*/  tf_ebp; int /*<<< orphan*/  tf_esi; int /*<<< orphan*/  tf_edi; int /*<<< orphan*/  tf_ds; int /*<<< orphan*/  tf_es; int /*<<< orphan*/  tf_fs; } ;
struct pcb {int /*<<< orphan*/  pcb_gs; } ;
typedef  int /*<<< orphan*/  regmap ;
struct TYPE_2__ {struct pcb* td_pcb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_DTRACE_ILLOP ; 
 int /*<<< orphan*/  DTRACE_CPUFLAG_SET (int /*<<< orphan*/ ) ; 
#define  REG_CS 144 
#define  REG_DS 143 
#define  REG_ERR 142 
#define  REG_ES 141 
#define  REG_FS 140 
#define  REG_GS 139 
#define  REG_RAX 138 
#define  REG_RBP 137 
#define  REG_RBX 136 
#define  REG_RCX 135 
#define  REG_RDI 134 
 int REG_RDX ; 
#define  REG_RFL 133 
#define  REG_RIP 132 
#define  REG_RSI 131 
#define  REG_RSP 130 
#define  REG_SS 129 
#define  REG_TRAPNO 128 
 int SS ; 
 TYPE_1__* curthread ; 

ulong_t
dtrace_getreg(struct trapframe *rp, uint_t reg)
{
	struct pcb *pcb;
	int regmap[] = {  /* Order is dependent on reg.d */
		REG_GS,		/* 0  GS */
		REG_FS,		/* 1  FS */
		REG_ES,		/* 2  ES */
		REG_DS,		/* 3  DS */
		REG_RDI,	/* 4  EDI */
		REG_RSI,	/* 5  ESI */
		REG_RBP,	/* 6  EBP, REG_FP */
		REG_RSP,	/* 7  ESP */
		REG_RBX,	/* 8  EBX */
		REG_RDX,	/* 9  EDX, REG_R1 */
		REG_RCX,	/* 10 ECX */
		REG_RAX,	/* 11 EAX, REG_R0 */
		REG_TRAPNO,	/* 12 TRAPNO */
		REG_ERR,	/* 13 ERR */
		REG_RIP,	/* 14 EIP, REG_PC */
		REG_CS,		/* 15 CS */
		REG_RFL,	/* 16 EFL, REG_PS */
		REG_RSP,	/* 17 UESP, REG_SP */
		REG_SS		/* 18 SS */
	};

	if (reg > SS) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}

	if (reg >= sizeof (regmap) / sizeof (int)) {
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}

	reg = regmap[reg];

	switch(reg) {
	case REG_GS:
		if ((pcb = curthread->td_pcb) == NULL) {
			DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
			return (0);
		}
		return (pcb->pcb_gs);
	case REG_FS:
		return (rp->tf_fs);
	case REG_ES:
		return (rp->tf_es);
	case REG_DS:
		return (rp->tf_ds);
	case REG_RDI:
		return (rp->tf_edi);
	case REG_RSI:
		return (rp->tf_esi);
	case REG_RBP:
		return (rp->tf_ebp);
	case REG_RSP:
		return (rp->tf_isp);
	case REG_RBX:
		return (rp->tf_ebx);
	case REG_RCX:
		return (rp->tf_ecx);
	case REG_RAX:
		return (rp->tf_eax);
	case REG_TRAPNO:
		return (rp->tf_trapno);
	case REG_ERR:
		return (rp->tf_err);
	case REG_RIP:
		return (rp->tf_eip);
	case REG_CS:
		return (rp->tf_cs);
	case REG_RFL:
		return (rp->tf_eflags);
#if 0
	case REG_RSP:
		return (rp->tf_esp);
#endif
	case REG_SS:
		return (rp->tf_ss);
	default:
		DTRACE_CPUFLAG_SET(CPU_DTRACE_ILLOP);
		return (0);
	}
}