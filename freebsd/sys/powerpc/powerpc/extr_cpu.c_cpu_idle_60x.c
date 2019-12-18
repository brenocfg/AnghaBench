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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sbintime_t ;
typedef  int register_t ;

/* Variables and functions */
#define  IBM970 135 
#define  IBM970FX 134 
#define  IBM970MP 133 
#define  MPC7447A 132 
#define  MPC7448 131 
#define  MPC7450 130 
#define  MPC7455 129 
#define  MPC7457 128 
 int PSL_POW ; 
 int mfmsr () ; 
 int mfpvr () ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  powerpc_pow_enabled ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static void
cpu_idle_60x(sbintime_t sbt)
{
	register_t msr;
	uint16_t vers;

	if (!powerpc_pow_enabled)
		return;

	msr = mfmsr();
	vers = mfpvr() >> 16;

#ifdef AIM
	switch (vers) {
	case IBM970:
	case IBM970FX:
	case IBM970MP:
	case MPC7447A:
	case MPC7448:
	case MPC7450:
	case MPC7455:
	case MPC7457:
		__asm __volatile("\
			    dssall; sync; mtmsr %0; isync"
			    :: "r"(msr | PSL_POW));
		break;
	default:
		powerpc_sync();
		mtmsr(msr | PSL_POW);
		break;
	}
#endif
}