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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct scb {int sg_list_busaddr; TYPE_1__* hscb; scalar_t__ sg_list; } ;
struct ahd_softc {int flags; } ;
struct ahd_dma_seg {int /*<<< orphan*/  len; scalar_t__ addr; } ;
struct ahd_dma64_seg {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgptr; int /*<<< orphan*/  datacnt; int /*<<< orphan*/  dataptr; } ;

/* Variables and functions */
 int AHD_39BIT_ADDRESSING ; 
 int AHD_64BIT_ADDRESSING ; 
 int SG_FULL_RESID ; 
 int /*<<< orphan*/  aic_htole32 (int) ; 
 int /*<<< orphan*/  aic_htole64 (int) ; 
 int aic_le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ahd_setup_data_scb(struct ahd_softc *ahd, struct scb *scb)
{
	/*
	 * Copy the first SG into the "current" data ponter area.
	 */
	if ((ahd->flags & AHD_64BIT_ADDRESSING) != 0) {
		struct ahd_dma64_seg *sg;

		sg = (struct ahd_dma64_seg *)scb->sg_list;
		scb->hscb->dataptr = sg->addr;
		scb->hscb->datacnt = sg->len;
	} else {
		struct ahd_dma_seg *sg;
		uint32_t *dataptr_words;

		sg = (struct ahd_dma_seg *)scb->sg_list;
		dataptr_words = (uint32_t*)&scb->hscb->dataptr;
		dataptr_words[0] = sg->addr;
		dataptr_words[1] = 0;
		if ((ahd->flags & AHD_39BIT_ADDRESSING) != 0) {
			uint64_t high_addr;

			high_addr = aic_le32toh(sg->len) & 0x7F000000;
			scb->hscb->dataptr |= aic_htole64(high_addr << 8);
		}
		scb->hscb->datacnt = sg->len;
	}
	/*
	 * Note where to find the SG entries in bus space.
	 * We also set the full residual flag which the 
	 * sequencer will clear as soon as a data transfer
	 * occurs.
	 */
	scb->hscb->sgptr = aic_htole32(scb->sg_list_busaddr|SG_FULL_RESID);
}