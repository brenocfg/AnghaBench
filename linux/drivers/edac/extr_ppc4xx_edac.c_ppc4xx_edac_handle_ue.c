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
typedef  int u64 ;
struct ppc4xx_ecc_status {int bearl; scalar_t__ bearh; } ;
struct mem_ctl_info {int nr_csrows; } ;
typedef  int /*<<< orphan*/  message ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int const PAGE_MASK ; 
 int const PAGE_SHIFT ; 
 int PPC4XX_EDAC_MESSAGE_SIZE ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,unsigned long const,unsigned long const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char*,char*) ; 
 scalar_t__ ppc4xx_edac_check_bank_error (struct ppc4xx_ecc_status const*,int) ; 
 int /*<<< orphan*/  ppc4xx_edac_generate_message (struct mem_ctl_info*,struct ppc4xx_ecc_status const*,char*,int) ; 

__attribute__((used)) static void
ppc4xx_edac_handle_ue(struct mem_ctl_info *mci,
		      const struct ppc4xx_ecc_status *status)
{
	const u64 bear = ((u64)status->bearh << 32 | status->bearl);
	const unsigned long page = bear >> PAGE_SHIFT;
	const unsigned long offset = bear & ~PAGE_MASK;
	int row;
	char message[PPC4XX_EDAC_MESSAGE_SIZE];

	ppc4xx_edac_generate_message(mci, status, message, sizeof(message));

	for (row = 0; row < mci->nr_csrows; row++)
		if (ppc4xx_edac_check_bank_error(status, row))
			edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
					     page, offset, 0,
					     row, 0, -1,
					     message, "");
}