#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint16_t ;
typedef  int u_register_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;
struct TYPE_4__ {scalar_t__ esr; } ;
struct TYPE_5__ {int /*<<< orphan*/  dsisr; } ;
struct TYPE_6__ {TYPE_1__ booke; TYPE_2__ aim; } ;
struct trapframe {TYPE_3__ cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESR_BITMASK ; 
#define  EXC_DSE 131 
#define  EXC_DSI 130 
#define  EXC_DTMISS 129 
#define  EXC_MCHK 128 
 int /*<<< orphan*/  MCSR_BITMASK ; 
 int /*<<< orphan*/  MPC745X_P (int) ; 
 int /*<<< orphan*/  MSSSR_BITMASK ; 
 int /*<<< orphan*/  SPR_MCAR ; 
 int /*<<< orphan*/  SPR_MCARU ; 
 int /*<<< orphan*/  SPR_MCSR ; 
 int /*<<< orphan*/  SPR_MSSSR0 ; 
 int mfpvr () ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
cpu_printtrap(u_int vector, struct trapframe *frame, int isfatal, int user)
{
#ifdef AIM
	uint16_t ver;

	switch (vector) {
	case EXC_DSE:
	case EXC_DSI:
	case EXC_DTMISS:
		printf("   dsisr           = 0x%lx\n",
		    (u_long)frame->cpu.aim.dsisr);
		break;
	case EXC_MCHK:
		ver = mfpvr() >> 16;
		if (MPC745X_P(ver))
			printf("    msssr0         = 0x%b\n",
			    (int)mfspr(SPR_MSSSR0), MSSSR_BITMASK);
		break;
	}
#elif defined(BOOKE)
	vm_paddr_t pa;

	switch (vector) {
	case EXC_MCHK:
		pa = mfspr(SPR_MCARU);
		pa = (pa << 32) | (u_register_t)mfspr(SPR_MCAR);
		printf("   mcsr            = 0x%b\n",
		    (int)mfspr(SPR_MCSR), MCSR_BITMASK);
		printf("   mcar            = 0x%jx\n", (uintmax_t)pa);
	}
	printf("   esr             = 0x%b\n",
	    (int)frame->cpu.booke.esr, ESR_BITMASK);
#endif
}