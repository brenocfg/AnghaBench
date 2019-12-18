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

/* Variables and functions */
 int /*<<< orphan*/  erratum_a15_798181 () ; 
 int /*<<< orphan*/  ipi_flush_tlb_a15_erratum ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void broadcast_tlb_a15_erratum(void)
{
	if (!erratum_a15_798181())
		return;

	smp_call_function(ipi_flush_tlb_a15_erratum, NULL, 1);
}