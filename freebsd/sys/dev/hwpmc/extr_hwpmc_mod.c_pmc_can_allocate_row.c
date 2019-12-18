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
typedef  enum pmc_mode { ____Placeholder_pmc_mode } pmc_mode ;
typedef  enum pmc_disp { ____Placeholder_pmc_disp } pmc_disp ;

/* Variables and functions */
 int /*<<< orphan*/  ALR ; 
 int EBUSY ; 
 int /*<<< orphan*/  PMC ; 
 int /*<<< orphan*/  PMCDBG2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int,int) ; 
 int PMC_DISP_STANDALONE ; 
 int PMC_DISP_THREAD ; 
 scalar_t__ PMC_IS_SYSTEM_MODE (int) ; 
 int /*<<< orphan*/  PMC_ROW_DISP_IS_FREE (int) ; 
 scalar_t__ PMC_ROW_DISP_IS_STANDALONE (int) ; 
 scalar_t__ PMC_ROW_DISP_IS_THREAD (int) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  pmc_sx ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmc_can_allocate_row(int ri, enum pmc_mode mode)
{
	enum pmc_disp	disp;

	sx_assert(&pmc_sx, SX_XLOCKED);

	PMCDBG2(PMC,ALR,1, "can-allocate-row ri=%d mode=%d", ri, mode);

	if (PMC_IS_SYSTEM_MODE(mode))
		disp = PMC_DISP_STANDALONE;
	else
		disp = PMC_DISP_THREAD;

	/*
	 * check disposition for PMC row 'ri':
	 *
	 * Expected disposition		Row-disposition		Result
	 *
	 * STANDALONE			STANDALONE or FREE	proceed
	 * STANDALONE			THREAD			fail
	 * THREAD			THREAD or FREE		proceed
	 * THREAD			STANDALONE		fail
	 */

	if (!PMC_ROW_DISP_IS_FREE(ri) &&
	    !(disp == PMC_DISP_THREAD && PMC_ROW_DISP_IS_THREAD(ri)) &&
	    !(disp == PMC_DISP_STANDALONE && PMC_ROW_DISP_IS_STANDALONE(ri)))
		return EBUSY;

	/*
	 * All OK
	 */

	PMCDBG2(PMC,ALR,2, "can-allocate-row ri=%d mode=%d ok", ri, mode);

	return 0;

}