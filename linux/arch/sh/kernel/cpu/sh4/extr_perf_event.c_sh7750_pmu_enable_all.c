#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMCR (int) ; 
 int PMCR_PMEN ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ sh7750_pmu ; 

__attribute__((used)) static void sh7750_pmu_enable_all(void)
{
	int i;

	for (i = 0; i < sh7750_pmu.num_events; i++)
		__raw_writew(__raw_readw(PMCR(i)) | PMCR_PMEN, PMCR(i));
}