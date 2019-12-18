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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  cntpct ; 
 int /*<<< orphan*/  cntvct ; 
 int /*<<< orphan*/  get_el0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 

__attribute__((used)) static uint64_t
get_cntxct(bool physical)
{
	uint64_t val;

	isb();
	if (physical)
		val = get_el0(cntpct);
	else
		val = get_el0(cntvct);

	return (val);
}