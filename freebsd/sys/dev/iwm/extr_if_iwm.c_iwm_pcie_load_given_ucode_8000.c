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
struct iwm_softc {int dummy; } ;
struct iwm_fw_img {scalar_t__ is_dual_cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DEBUG_RESET ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  IWM_RELEASE_CPU_RESET ; 
 int /*<<< orphan*/  IWM_RELEASE_CPU_RESET_BIT ; 
 scalar_t__ iwm_nic_lock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_nic_unlock (struct iwm_softc*) ; 
 int iwm_pcie_load_cpu_sections_8000 (struct iwm_softc*,struct iwm_fw_img const*,int,int*) ; 
 int /*<<< orphan*/  iwm_write_prph (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
iwm_pcie_load_given_ucode_8000(struct iwm_softc *sc,
	const struct iwm_fw_img *image)
{
	int ret = 0;
	int first_ucode_section;

	IWM_DPRINTF(sc, IWM_DEBUG_RESET, "working with %s CPU\n",
		    image->is_dual_cpus ? "Dual" : "Single");

	/* configure the ucode to be ready to get the secured image */
	/* release CPU reset */
	if (iwm_nic_lock(sc)) {
		iwm_write_prph(sc, IWM_RELEASE_CPU_RESET,
		    IWM_RELEASE_CPU_RESET_BIT);
		iwm_nic_unlock(sc);
	}

	/* load to FW the binary Secured sections of CPU1 */
	ret = iwm_pcie_load_cpu_sections_8000(sc, image, 1,
	    &first_ucode_section);
	if (ret)
		return ret;

	/* load to FW the binary sections of CPU2 */
	return iwm_pcie_load_cpu_sections_8000(sc, image, 2,
	    &first_ucode_section);
}