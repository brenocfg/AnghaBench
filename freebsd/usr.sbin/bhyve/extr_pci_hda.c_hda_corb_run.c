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
typedef  int /*<<< orphan*/  uint32_t ;
struct hda_codec_cmd_ctl {int wp; int rp; int size; scalar_t__ run; scalar_t__ dma_vaddr; } ;
struct hda_softc {struct hda_codec_cmd_ctl corb; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDAC_CORBRP ; 
 int /*<<< orphan*/  HDAC_CORBWP ; 
 int HDA_CORB_ENTRY_LEN ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hda_dma_ld_dword (scalar_t__) ; 
 int hda_get_reg_by_offset (struct hda_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_response_interrupt (struct hda_softc*) ; 
 int hda_send_command (struct hda_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_set_reg_by_offset (struct hda_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hda_corb_run(struct hda_softc *sc)
{
	struct hda_codec_cmd_ctl *corb = &sc->corb;
	uint32_t verb = 0;
	int err;

	corb->wp = hda_get_reg_by_offset(sc, HDAC_CORBWP);

	while (corb->rp != corb->wp && corb->run) {
		corb->rp++;
		corb->rp %= corb->size;

		verb = hda_dma_ld_dword(corb->dma_vaddr +		\
				HDA_CORB_ENTRY_LEN * corb->rp);

		err = hda_send_command(sc, verb);
		assert(!err);
	}

	hda_set_reg_by_offset(sc, HDAC_CORBRP, corb->rp);

	if (corb->run)
		hda_response_interrupt(sc);

	return (0);
}