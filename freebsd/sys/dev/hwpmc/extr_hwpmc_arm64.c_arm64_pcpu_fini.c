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
struct pmc_mdep {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCR_E ; 
 int /*<<< orphan*/  arm64_pmcr_read () ; 
 int /*<<< orphan*/  arm64_pmcr_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm64_pcpu_fini(struct pmc_mdep *md, int cpu)
{
	uint32_t pmcr;

	pmcr = arm64_pmcr_read();
	pmcr &= ~PMCR_E;
	arm64_pmcr_write(pmcr);

	return (0);
}