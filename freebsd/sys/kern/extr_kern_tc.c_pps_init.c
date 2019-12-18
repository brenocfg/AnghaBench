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
struct pps_state {int ppscap; int /*<<< orphan*/  kcmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCMODE_ABIFLAG ; 
 int PPS_CANWAIT ; 
 int PPS_CAPTUREASSERT ; 
 int PPS_CAPTURECLEAR ; 
 int PPS_OFFSETASSERT ; 
 int PPS_OFFSETCLEAR ; 
 int PPS_TSCLK_MASK ; 
 int PPS_TSFMT_TSPEC ; 

void
pps_init(struct pps_state *pps)
{
	pps->ppscap |= PPS_TSFMT_TSPEC | PPS_CANWAIT;
	if (pps->ppscap & PPS_CAPTUREASSERT)
		pps->ppscap |= PPS_OFFSETASSERT;
	if (pps->ppscap & PPS_CAPTURECLEAR)
		pps->ppscap |= PPS_OFFSETCLEAR;
#ifdef FFCLOCK
	pps->ppscap |= PPS_TSCLK_MASK;
#endif
	pps->kcmode &= ~KCMODE_ABIFLAG;
}