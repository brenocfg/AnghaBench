#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int mode; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_ciu_wdogx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_PP_POKEX (int) ; 
 int /*<<< orphan*/  CVMX_CIU_WDOGX (int) ; 
 int /*<<< orphan*/  DEFAULT_TIMER_VAL ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
octeon_watchdog_arm_core(int core)
{
	cvmx_ciu_wdogx_t ciu_wdog;

	/* Poke it! */
	cvmx_write_csr(CVMX_CIU_PP_POKEX(core), 1);

	/*
	 * XXX
	 * Perhaps if KDB is enabled, we should use mode=2 and drop into the
	 * debugger on NMI?
	 *
	 * XXX
	 * Timer should be calculated based on CPU frquency
	 */
	ciu_wdog.u64 = 0;
	ciu_wdog.s.len = DEFAULT_TIMER_VAL;
	ciu_wdog.s.mode = 3;
	cvmx_write_csr(CVMX_CIU_WDOGX(core), ciu_wdog.u64);
}