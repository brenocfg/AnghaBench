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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  cntpct ; 
 int /*<<< orphan*/  cntvct ; 
 int get_el0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isb () ; 

__attribute__((used)) static uint64_t
get_cntxct_a64_unstable(bool physical)
{
	uint64_t val
;
	isb();
	if (physical) {
		do {
			val = get_el0(cntpct);
		}
		while (((val + 1) & 0x7FF) <= 1);
	}
	else {
		do {
			val = get_el0(cntvct);
		}
		while (((val + 1) & 0x7FF) <= 1);
	}

	return (val);
}