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
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
struct urtw_softc {int sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_8187B_8225_ANAPARAM2_OFF ; 
 int /*<<< orphan*/  URTW_8187B_8225_ANAPARAM3_OFF ; 
 int /*<<< orphan*/  URTW_8187B_8225_ANAPARAM_OFF ; 
 int /*<<< orphan*/  URTW_8225_ANAPARAM2_OFF ; 
 int /*<<< orphan*/  URTW_8225_ANAPARAM_OFF ; 
 int /*<<< orphan*/  URTW_ANAPARAM ; 
 int /*<<< orphan*/  URTW_ANAPARAM2 ; 
 int /*<<< orphan*/  URTW_ANAPARAM3 ; 
 int /*<<< orphan*/  URTW_CONFIG3 ; 
 int URTW_CONFIG3_ANAPARAM_WRITE ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_CONFIG ; 
 int /*<<< orphan*/  URTW_EPROM_CMD_NORMAL ; 
 int URTW_RTL8187B ; 
 int /*<<< orphan*/  urtw_8225_write (struct urtw_softc*,int,int) ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ urtw_set_mode (struct urtw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write32_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static usb_error_t
urtw_8225_rf_stop(struct urtw_softc *sc)
{
	uint8_t data;
	usb_error_t error;

	urtw_8225_write(sc, 0x4, 0x1f);

	error = urtw_set_mode(sc, URTW_EPROM_CMD_CONFIG);
	if (error)
		goto fail;

	urtw_read8_m(sc, URTW_CONFIG3, &data);
	urtw_write8_m(sc, URTW_CONFIG3, data | URTW_CONFIG3_ANAPARAM_WRITE);
	if (sc->sc_flags & URTW_RTL8187B) {
		urtw_write32_m(sc, URTW_ANAPARAM2,
		    URTW_8187B_8225_ANAPARAM2_OFF);
		urtw_write32_m(sc, URTW_ANAPARAM, URTW_8187B_8225_ANAPARAM_OFF);
		urtw_write32_m(sc, URTW_ANAPARAM3,
		    URTW_8187B_8225_ANAPARAM3_OFF);
	} else {
		urtw_write32_m(sc, URTW_ANAPARAM2, URTW_8225_ANAPARAM2_OFF);
		urtw_write32_m(sc, URTW_ANAPARAM, URTW_8225_ANAPARAM_OFF);
	}

	urtw_write8_m(sc, URTW_CONFIG3, data & ~URTW_CONFIG3_ANAPARAM_WRITE);
	error = urtw_set_mode(sc, URTW_EPROM_CMD_NORMAL);
	if (error)
		goto fail;

fail:
	return (error);
}