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
struct ppc_data {int ppc_avm; int ppc_flags; int /*<<< orphan*/  ppc_mode; } ;

/* Variables and functions */
 int EIO ; 
 int PPB_COMPATIBLE ; 
 int PPB_ECP ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  ppc_detect_fifo (struct ppc_data*) ; 
 int /*<<< orphan*/  ppc_detect_port (struct ppc_data*) ; 
 int /*<<< orphan*/  ppc_generic_detect (struct ppc_data*,int) ; 
 int /*<<< orphan*/  ppc_pc873xx_detect ; 
 int /*<<< orphan*/  ppc_smc37c66xgt_detect ; 
 int /*<<< orphan*/  ppc_smc37c935_detect ; 
 int /*<<< orphan*/  ppc_w83877f_detect ; 
 int /*<<< orphan*/  printf (char*) ; 
 int stub1 (struct ppc_data*,int) ; 

__attribute__((used)) static int
ppc_detect(struct ppc_data *ppc, int chipset_mode) {

#ifdef PPC_PROBE_CHIPSET
	int i, mode;

	/* list of supported chipsets */
	int (*chipset_detect[])(struct ppc_data *, int) = {
		ppc_pc873xx_detect,
		ppc_smc37c66xgt_detect,
		ppc_w83877f_detect,
		ppc_smc37c935_detect,
		ppc_generic_detect,
		NULL
	};
#endif

	/* if can't find the port and mode not forced return error */
	if (!ppc_detect_port(ppc) && chipset_mode == 0)
		return (EIO);			/* failed, port not present */

	/* assume centronics compatible mode is supported */
	ppc->ppc_avm = PPB_COMPATIBLE;

#ifdef PPC_PROBE_CHIPSET
	/* we have to differenciate available chipset modes,
	 * chipset running modes and IEEE-1284 operating modes
	 *
	 * after detection, the port must support running in compatible mode
	 */
	if (ppc->ppc_flags & 0x40) {
		if (bootverbose)
			printf("ppc: chipset forced to generic\n");
#endif

		ppc->ppc_mode = ppc_generic_detect(ppc, chipset_mode);

#ifdef PPC_PROBE_CHIPSET
	} else {
		for (i=0; chipset_detect[i] != NULL; i++) {
			if ((mode = chipset_detect[i](ppc, chipset_mode)) != -1) {
				ppc->ppc_mode = mode;
				break;
			}
		}
	}
#endif

	/* configure/detect ECP FIFO */
	if ((ppc->ppc_avm & PPB_ECP) && !(ppc->ppc_flags & 0x80))
		ppc_detect_fifo(ppc);

	return (0);
}