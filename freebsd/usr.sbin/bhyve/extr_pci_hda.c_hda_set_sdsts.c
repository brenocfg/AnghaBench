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
typedef  int uint32_t ;
struct hda_softc {int dummy; } ;

/* Variables and functions */
 int HDA_SDSTS_IRQ_MASK ; 
 int hda_get_reg_by_offset (struct hda_softc*,int) ; 
 int /*<<< orphan*/  hda_set_field_by_offset (struct hda_softc*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_set_reg_by_offset (struct hda_softc*,int,int) ; 
 int /*<<< orphan*/  hda_update_intr (struct hda_softc*) ; 

__attribute__((used)) static void
hda_set_sdsts(struct hda_softc *sc, uint32_t offset, uint32_t old)
{
	uint32_t value = hda_get_reg_by_offset(sc, offset);

	hda_set_reg_by_offset(sc, offset, old);

	/* clear the corresponding bits written by the software (guest) */
	hda_set_field_by_offset(sc, offset, value & HDA_SDSTS_IRQ_MASK, 0);

	hda_update_intr(sc);
}