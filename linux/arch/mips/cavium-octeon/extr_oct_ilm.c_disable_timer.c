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
struct TYPE_2__ {scalar_t__ len; scalar_t__ one_shot; } ;
union cvmx_ciu_timx {int /*<<< orphan*/  u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_TIMX (int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_timer(int timer)
{
	union cvmx_ciu_timx timx;

	timx.s.one_shot = 0;
	timx.s.len = 0;
	cvmx_write_csr(CVMX_CIU_TIMX(timer), timx.u64);
	/* Read it back to force immediate write of timer register*/
	timx.u64 = cvmx_read_csr(CVMX_CIU_TIMX(timer));
}