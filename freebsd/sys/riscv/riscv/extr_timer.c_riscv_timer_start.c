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
typedef  int uint32_t ;
struct eventtimer {scalar_t__ et_frequency; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SIE_STIE ; 
 int /*<<< orphan*/  csr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_cycles () ; 
 int /*<<< orphan*/  sbi_set_timer (scalar_t__) ; 
 int /*<<< orphan*/  sie ; 

__attribute__((used)) static int
riscv_timer_start(struct eventtimer *et, sbintime_t first, sbintime_t period)
{
	uint64_t counts;

	if (first != 0) {
		counts = ((uint32_t)et->et_frequency * first) >> 32;
		sbi_set_timer(get_cycles() + counts);
		csr_set(sie, SIE_STIE);

		return (0);
	}

	return (EINVAL);

}