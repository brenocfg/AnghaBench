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
typedef  int uint8_t ;
struct hda_softc {scalar_t__ rirb_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDAC_RIRBCTL ; 
 int HDAC_RIRBCTL_RINTCTL ; 
 int /*<<< orphan*/  HDAC_RIRBSTS ; 
 int /*<<< orphan*/  HDAC_RIRBSTS_RINTFL ; 
 int hda_get_reg_by_offset (struct hda_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_set_field_by_offset (struct hda_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_update_intr (struct hda_softc*) ; 

__attribute__((used)) static void
hda_response_interrupt(struct hda_softc *sc)
{
	uint8_t rirbctl = hda_get_reg_by_offset(sc, HDAC_RIRBCTL);

	if ((rirbctl & HDAC_RIRBCTL_RINTCTL) && sc->rirb_cnt) {
		sc->rirb_cnt = 0;
		hda_set_field_by_offset(sc, HDAC_RIRBSTS, HDAC_RIRBSTS_RINTFL,
				HDAC_RIRBSTS_RINTFL);
		hda_update_intr(sc);
	}
}