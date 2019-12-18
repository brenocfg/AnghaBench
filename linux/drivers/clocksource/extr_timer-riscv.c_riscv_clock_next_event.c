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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIE_STIE ; 
 int /*<<< orphan*/  csr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_cycles64 () ; 
 int /*<<< orphan*/  sbi_set_timer (scalar_t__) ; 
 int /*<<< orphan*/  sie ; 

__attribute__((used)) static int riscv_clock_next_event(unsigned long delta,
		struct clock_event_device *ce)
{
	csr_set(sie, SIE_STIE);
	sbi_set_timer(get_cycles64() + delta);
	return 0;
}