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
struct ppc4xx_ecc_status {int ecces; } ;
struct mem_ctl_info {int dummy; } ;

/* Variables and functions */
 int SDRAM_ECCES_CE ; 
 int SDRAM_ECCES_UE ; 
 int /*<<< orphan*/  ppc4xx_ecc_clear_status (struct mem_ctl_info*,struct ppc4xx_ecc_status*) ; 
 int /*<<< orphan*/  ppc4xx_ecc_dump_status (struct mem_ctl_info*,struct ppc4xx_ecc_status*) ; 
 int /*<<< orphan*/  ppc4xx_ecc_get_status (struct mem_ctl_info*,struct ppc4xx_ecc_status*) ; 
 int /*<<< orphan*/  ppc4xx_edac_handle_ce (struct mem_ctl_info*,struct ppc4xx_ecc_status*) ; 
 int /*<<< orphan*/  ppc4xx_edac_handle_ue (struct mem_ctl_info*,struct ppc4xx_ecc_status*) ; 

__attribute__((used)) static void
ppc4xx_edac_check(struct mem_ctl_info *mci)
{
#ifdef DEBUG
	static unsigned int count;
#endif
	struct ppc4xx_ecc_status status;

	ppc4xx_ecc_get_status(mci, &status);

#ifdef DEBUG
	if (count++ % 30 == 0)
		ppc4xx_ecc_dump_status(mci, &status);
#endif

	if (status.ecces & SDRAM_ECCES_UE)
		ppc4xx_edac_handle_ue(mci, &status);

	if (status.ecces & SDRAM_ECCES_CE)
		ppc4xx_edac_handle_ce(mci, &status);

	ppc4xx_ecc_clear_status(mci, &status);
}