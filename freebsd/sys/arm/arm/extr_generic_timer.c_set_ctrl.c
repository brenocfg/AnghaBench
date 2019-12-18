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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cntp_ctl ; 
 int /*<<< orphan*/  cntv_ctl ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  set_el0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_ctrl(uint32_t val, bool physical)
{

	if (physical)
		set_el0(cntp_ctl, val);
	else
		set_el0(cntv_ctl, val);
	isb();

	return (0);
}