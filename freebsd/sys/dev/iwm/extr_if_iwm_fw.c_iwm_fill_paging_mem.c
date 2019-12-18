#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct iwm_softc {int num_of_paging_blk; int num_of_pages_in_last_blk; TYPE_2__* fw_paging_db; int /*<<< orphan*/  sc_dev; } ;
struct iwm_fw_img {TYPE_3__* sec; } ;
struct TYPE_6__ {scalar_t__ offset; char const* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  vaddr; } ;
struct TYPE_5__ {int fw_paging_size; TYPE_1__ fw_paging_block; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWM_DEBUG_FW ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,int,...) ; 
 int IWM_FW_PAGING_SIZE ; 
 scalar_t__ IWM_PAGING_SEPARATOR_SECTION ; 
 int IWM_UCODE_SECTION_MAX ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iwm_free_fw_paging (struct iwm_softc*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int nitems (TYPE_3__*) ; 

__attribute__((used)) static int
iwm_fill_paging_mem(struct iwm_softc *sc, const struct iwm_fw_img *image)
{
	int sec_idx, idx;
	uint32_t offset = 0;

	/*
	 * find where is the paging image start point:
	 * if CPU2 exist and it's in paging format, then the image looks like:
	 * CPU1 sections (2 or more)
	 * CPU1_CPU2_SEPARATOR_SECTION delimiter - separate between CPU1 to CPU2
	 * CPU2 sections (not paged)
	 * PAGING_SEPARATOR_SECTION delimiter - separate between CPU2
	 * non paged to CPU2 paging sec
	 * CPU2 paging CSS
	 * CPU2 paging image (including instruction and data)
	 */
	for (sec_idx = 0; sec_idx < IWM_UCODE_SECTION_MAX; sec_idx++) {
		if (image->sec[sec_idx].offset == IWM_PAGING_SEPARATOR_SECTION) {
			sec_idx++;
			break;
		}
	}

	/*
	 * If paging is enabled there should be at least 2 more sections left
	 * (one for CSS and one for Paging data)
	 */
	if (sec_idx >= nitems(image->sec) - 1) {
		device_printf(sc->sc_dev,
		    "Paging: Missing CSS and/or paging sections\n");
		iwm_free_fw_paging(sc);
		return EINVAL;
	}

	/* copy the CSS block to the dram */
	IWM_DPRINTF(sc, IWM_DEBUG_FW,
		    "Paging: load paging CSS to FW, sec = %d\n",
		    sec_idx);

	memcpy(sc->fw_paging_db[0].fw_paging_block.vaddr,
	       image->sec[sec_idx].data,
	       sc->fw_paging_db[0].fw_paging_size);

	IWM_DPRINTF(sc, IWM_DEBUG_FW,
		    "Paging: copied %d CSS bytes to first block\n",
		    sc->fw_paging_db[0].fw_paging_size);

	sec_idx++;

	/*
	 * copy the paging blocks to the dram
	 * loop index start from 1 since that CSS block already copied to dram
	 * and CSS index is 0.
	 * loop stop at num_of_paging_blk since that last block is not full.
	 */
	for (idx = 1; idx < sc->num_of_paging_blk; idx++) {
		memcpy(sc->fw_paging_db[idx].fw_paging_block.vaddr,
		       (const char *)image->sec[sec_idx].data + offset,
		       sc->fw_paging_db[idx].fw_paging_size);

		IWM_DPRINTF(sc, IWM_DEBUG_FW,
			    "Paging: copied %d paging bytes to block %d\n",
			    sc->fw_paging_db[idx].fw_paging_size,
			    idx);

		offset += sc->fw_paging_db[idx].fw_paging_size;
	}

	/* copy the last paging block */
	if (sc->num_of_pages_in_last_blk > 0) {
		memcpy(sc->fw_paging_db[idx].fw_paging_block.vaddr,
		       (const char *)image->sec[sec_idx].data + offset,
		       IWM_FW_PAGING_SIZE * sc->num_of_pages_in_last_blk);

		IWM_DPRINTF(sc, IWM_DEBUG_FW,
			    "Paging: copied %d pages in the last block %d\n",
			    sc->num_of_pages_in_last_blk, idx);
	}

	return 0;
}