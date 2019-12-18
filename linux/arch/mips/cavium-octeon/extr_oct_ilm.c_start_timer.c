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
struct TYPE_3__ {int one_shot; int /*<<< orphan*/  len; } ;
union cvmx_ciu_timx {scalar_t__ u64; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {void* timer_start2; void* timer_start1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_TIMX (int) ; 
 scalar_t__ cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__ li ; 
 int /*<<< orphan*/  raw_local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  raw_local_irq_save (unsigned long) ; 
 void* read_c0_cvmcount () ; 

__attribute__((used)) static void start_timer(int timer, u64 interval)
{
	union cvmx_ciu_timx timx;
	unsigned long flags;

	timx.u64 = 0;
	timx.s.one_shot = 1;
	timx.s.len = interval;
	raw_local_irq_save(flags);
	li.timer_start1 = read_c0_cvmcount();
	cvmx_write_csr(CVMX_CIU_TIMX(timer), timx.u64);
	/* Read it back to force wait until register is written. */
	timx.u64 = cvmx_read_csr(CVMX_CIU_TIMX(timer));
	li.timer_start2 = read_c0_cvmcount();
	raw_local_irq_restore(flags);
}