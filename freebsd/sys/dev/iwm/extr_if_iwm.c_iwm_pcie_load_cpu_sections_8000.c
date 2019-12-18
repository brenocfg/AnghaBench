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
typedef  int uint32_t ;
struct iwm_softc {int dummy; } ;
struct iwm_fw_img {TYPE_1__* sec; } ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ IWM_CPU1_CPU2_SEPARATOR_SECTION ; 
 int /*<<< orphan*/  IWM_DEBUG_RESET ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  IWM_FH_UCODE_LOAD_STATUS ; 
 scalar_t__ IWM_PAGING_SEPARATOR_SECTION ; 
 int IWM_READ (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int IWM_UCODE_SECTION_MAX ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwm_enable_interrupts (struct iwm_softc*) ; 
 scalar_t__ iwm_nic_lock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_nic_unlock (struct iwm_softc*) ; 
 int iwm_pcie_load_section (struct iwm_softc*,int,TYPE_1__*) ; 

__attribute__((used)) static int
iwm_pcie_load_cpu_sections_8000(struct iwm_softc *sc,
	const struct iwm_fw_img *image, int cpu, int *first_ucode_section)
{
	int shift_param;
	int i, ret = 0, sec_num = 0x1;
	uint32_t val, last_read_idx = 0;

	if (cpu == 1) {
		shift_param = 0;
		*first_ucode_section = 0;
	} else {
		shift_param = 16;
		(*first_ucode_section)++;
	}

	for (i = *first_ucode_section; i < IWM_UCODE_SECTION_MAX; i++) {
		last_read_idx = i;

		/*
		 * CPU1_CPU2_SEPARATOR_SECTION delimiter - separate between
		 * CPU1 to CPU2.
		 * PAGING_SEPARATOR_SECTION delimiter - separate between
		 * CPU2 non paged to CPU2 paging sec.
		 */
		if (!image->sec[i].data ||
		    image->sec[i].offset == IWM_CPU1_CPU2_SEPARATOR_SECTION ||
		    image->sec[i].offset == IWM_PAGING_SEPARATOR_SECTION) {
			IWM_DPRINTF(sc, IWM_DEBUG_RESET,
				    "Break since Data not valid or Empty section, sec = %d\n",
				    i);
			break;
		}
		ret = iwm_pcie_load_section(sc, i, &image->sec[i]);
		if (ret)
			return ret;

		/* Notify the ucode of the loaded section number and status */
		if (iwm_nic_lock(sc)) {
			val = IWM_READ(sc, IWM_FH_UCODE_LOAD_STATUS);
			val = val | (sec_num << shift_param);
			IWM_WRITE(sc, IWM_FH_UCODE_LOAD_STATUS, val);
			sec_num = (sec_num << 1) | 0x1;
			iwm_nic_unlock(sc);
		}
	}

	*first_ucode_section = last_read_idx;

	iwm_enable_interrupts(sc);

	if (iwm_nic_lock(sc)) {
		if (cpu == 1)
			IWM_WRITE(sc, IWM_FH_UCODE_LOAD_STATUS, 0xFFFF);
		else
			IWM_WRITE(sc, IWM_FH_UCODE_LOAD_STATUS, 0xFFFFFFFF);
		iwm_nic_unlock(sc);
	}

	return 0;
}