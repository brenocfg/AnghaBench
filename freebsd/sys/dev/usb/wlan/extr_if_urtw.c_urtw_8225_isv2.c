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
typedef  scalar_t__ uint32_t ;
struct urtw_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_8225_ADDR_0_DATA_MAGIC1 ; 
 int /*<<< orphan*/  URTW_8225_ADDR_0_DATA_MAGIC2 ; 
 int /*<<< orphan*/  URTW_8225_ADDR_0_MAGIC ; 
 scalar_t__ URTW_8225_ADDR_8_DATA_MAGIC1 ; 
 int /*<<< orphan*/  URTW_8225_ADDR_8_MAGIC ; 
 scalar_t__ URTW_8225_ADDR_9_DATA_MAGIC1 ; 
 int /*<<< orphan*/  URTW_8225_ADDR_9_MAGIC ; 
 int /*<<< orphan*/  URTW_RF_PINS_ENABLE ; 
 int /*<<< orphan*/  URTW_RF_PINS_MAGIC5 ; 
 int /*<<< orphan*/  URTW_RF_PINS_OUTPUT ; 
 int /*<<< orphan*/  URTW_RF_PINS_SELECT ; 
 scalar_t__ urtw_8225_read (struct urtw_softc*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  urtw_8225_write (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  urtw_write16_m (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8225_isv2(struct urtw_softc *sc, int *ret)
{
	uint32_t data;
	usb_error_t error;

	*ret = 1;

	urtw_write16_m(sc, URTW_RF_PINS_OUTPUT, URTW_RF_PINS_MAGIC5);
	urtw_write16_m(sc, URTW_RF_PINS_SELECT, URTW_RF_PINS_MAGIC5);
	urtw_write16_m(sc, URTW_RF_PINS_ENABLE, URTW_RF_PINS_MAGIC5);
	usb_pause_mtx(&sc->sc_mtx, 500);

	urtw_8225_write(sc, URTW_8225_ADDR_0_MAGIC,
	    URTW_8225_ADDR_0_DATA_MAGIC1);

	error = urtw_8225_read(sc, URTW_8225_ADDR_8_MAGIC, &data);
	if (error != 0)
		goto fail;
	if (data != URTW_8225_ADDR_8_DATA_MAGIC1)
		*ret = 0;
	else {
		error = urtw_8225_read(sc, URTW_8225_ADDR_9_MAGIC, &data);
		if (error != 0)
			goto fail;
		if (data != URTW_8225_ADDR_9_DATA_MAGIC1)
			*ret = 0;
	}

	urtw_8225_write(sc, URTW_8225_ADDR_0_MAGIC,
	    URTW_8225_ADDR_0_DATA_MAGIC2);
fail:
	return (error);
}