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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ U300_SYSCON_CCR ; 
 int /*<<< orphan*/  U300_SYSCON_CCR_CLKING_PERFORMANCE_MASK ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 scalar_t__ syscon_vbase ; 

__attribute__((used)) static u16 syscon_get_perf(void)
{
	u16 val;

	val = readw(syscon_vbase + U300_SYSCON_CCR);
	val &= U300_SYSCON_CCR_CLKING_PERFORMANCE_MASK;
	return val;
}