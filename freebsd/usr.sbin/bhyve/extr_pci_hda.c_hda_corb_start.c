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
typedef  size_t uint8_t ;
typedef  int uint64_t ;
struct hda_codec_cmd_ctl {char* name; int size; int wp; int rp; int run; int /*<<< orphan*/  dma_vaddr; } ;
struct hda_softc {struct hda_codec_cmd_ctl corb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  HDAC_CORBLBASE ; 
 int /*<<< orphan*/  HDAC_CORBRP ; 
 int /*<<< orphan*/  HDAC_CORBSIZE ; 
 int HDAC_CORBSIZE_CORBSIZE_MASK ; 
 int /*<<< orphan*/  HDAC_CORBUBASE ; 
 int /*<<< orphan*/  HDAC_CORBWP ; 
 int HDA_CORB_ENTRY_LEN ; 
 int* hda_corb_sizes ; 
 int /*<<< orphan*/  hda_dma_get_vaddr (struct hda_softc*,int,int) ; 
 int hda_get_reg_by_offset (struct hda_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_print_cmd_ctl_data (struct hda_codec_cmd_ctl*) ; 

__attribute__((used)) static int
hda_corb_start(struct hda_softc *sc)
{
	struct hda_codec_cmd_ctl *corb = &sc->corb;
	uint8_t corbsize = 0;
	uint64_t corblbase = 0;
	uint64_t corbubase = 0;
	uint64_t corbpaddr = 0;

	corb->name = "CORB";

	corbsize = hda_get_reg_by_offset(sc, HDAC_CORBSIZE) &		\
		   HDAC_CORBSIZE_CORBSIZE_MASK;
	corb->size = hda_corb_sizes[corbsize];

	if (!corb->size) {
		DPRINTF("Invalid corb size\n");
		return (-1);
	}

	corblbase = hda_get_reg_by_offset(sc, HDAC_CORBLBASE);
	corbubase = hda_get_reg_by_offset(sc, HDAC_CORBUBASE);

	corbpaddr = corblbase | (corbubase << 32);
	DPRINTF("CORB dma_paddr: %p\n", (void *)corbpaddr);

	corb->dma_vaddr = hda_dma_get_vaddr(sc, corbpaddr,
			HDA_CORB_ENTRY_LEN * corb->size);
	if (!corb->dma_vaddr) {
		DPRINTF("Fail to get the guest virtual address\n");
		return (-1);
	}

	corb->wp = hda_get_reg_by_offset(sc, HDAC_CORBWP);
	corb->rp = hda_get_reg_by_offset(sc, HDAC_CORBRP);

	corb->run = 1;

	hda_print_cmd_ctl_data(corb);

	return (0);
}