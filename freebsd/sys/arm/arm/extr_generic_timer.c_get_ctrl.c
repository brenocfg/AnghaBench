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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  cntp_ctl ; 
 int /*<<< orphan*/  cntv_ctl ; 
 int get_el0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_ctrl(bool physical)
{
	uint32_t val;

	if (physical)
		val = get_el0(cntp_ctl);
	else
		val = get_el0(cntv_ctl);

	return (val);
}