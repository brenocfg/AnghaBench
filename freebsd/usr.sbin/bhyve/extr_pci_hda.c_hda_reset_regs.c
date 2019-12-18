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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct hda_softc {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 scalar_t__ HDAC_CORBSIZE ; 
 int HDAC_CORBSIZE_CORBSIZE_256 ; 
 int HDAC_CORBSIZE_CORBSZCAP_256 ; 
 scalar_t__ HDAC_GCAP ; 
 int HDAC_GCAP_64OK ; 
 int HDAC_GCAP_ISS_SHIFT ; 
 int HDAC_GCAP_OSS_SHIFT ; 
 scalar_t__ HDAC_INPAY ; 
 scalar_t__ HDAC_OUTPAY ; 
 scalar_t__ HDAC_RIRBSIZE ; 
 int HDAC_RIRBSIZE_RIRBSIZE_256 ; 
 int HDAC_RIRBSIZE_RIRBSZCAP_256 ; 
 scalar_t__ HDAC_SDFIFOS ; 
 scalar_t__ HDAC_VMAJ ; 
 int HDA_FIFO_SIZE ; 
 scalar_t__ HDA_IOSS_NO ; 
 int HDA_ISS_NO ; 
 int HDA_OSS_NO ; 
 scalar_t__ hda_get_offset_stream (scalar_t__) ; 
 int /*<<< orphan*/  hda_set_reg_by_offset (struct hda_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hda_reset_regs(struct hda_softc *sc)
{
	uint32_t off = 0;
	uint8_t i;

	DPRINTF("Reset the HDA controller registers ...\n");

	memset(sc->regs, 0, sizeof(sc->regs));

	hda_set_reg_by_offset(sc, HDAC_GCAP,
			HDAC_GCAP_64OK |
			(HDA_ISS_NO << HDAC_GCAP_ISS_SHIFT) |
			(HDA_OSS_NO << HDAC_GCAP_OSS_SHIFT));
	hda_set_reg_by_offset(sc, HDAC_VMAJ, 0x01);
	hda_set_reg_by_offset(sc, HDAC_OUTPAY, 0x3c);
	hda_set_reg_by_offset(sc, HDAC_INPAY, 0x1d);
	hda_set_reg_by_offset(sc, HDAC_CORBSIZE,
	    HDAC_CORBSIZE_CORBSZCAP_256 | HDAC_CORBSIZE_CORBSIZE_256);
	hda_set_reg_by_offset(sc, HDAC_RIRBSIZE,
	    HDAC_RIRBSIZE_RIRBSZCAP_256 | HDAC_RIRBSIZE_RIRBSIZE_256);

	for (i = 0; i < HDA_IOSS_NO; i++) {
		off = hda_get_offset_stream(i);
		hda_set_reg_by_offset(sc, off + HDAC_SDFIFOS, HDA_FIFO_SIZE);
	}
}