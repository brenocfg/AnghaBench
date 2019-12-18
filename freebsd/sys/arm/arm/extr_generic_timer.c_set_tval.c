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
 int /*<<< orphan*/  cntp_tval ; 
 int /*<<< orphan*/  cntv_tval ; 
 int /*<<< orphan*/  isb () ; 
 int /*<<< orphan*/  set_el0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_tval(uint32_t val, bool physical)
{

	if (physical)
		set_el0(cntp_tval, val);
	else
		set_el0(cntv_tval, val);
	isb();

	return (0);
}