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
typedef  int usb_error_t ;
struct urtw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_8225_ADDR_C_DATA_MAGIC1 ; 
 int /*<<< orphan*/  URTW_8225_ADDR_C_DATA_MAGIC2 ; 
 int /*<<< orphan*/  URTW_8225_ADDR_C_MAGIC ; 
 int /*<<< orphan*/  urtw_8187_write_phy_cck (struct urtw_softc*,int,int /*<<< orphan*/ ) ; 
 int urtw_8225_setgain (struct urtw_softc*,int) ; 
 int /*<<< orphan*/ * urtw_8225_threshold ; 
 int /*<<< orphan*/  urtw_8225_write (struct urtw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
urtw_8225_rf_set_sens(struct urtw_softc *sc, int sens)
{
	usb_error_t error;

	if (sens < 0 || sens > 6)
		return -1;

	if (sens > 4)
		urtw_8225_write(sc,
		    URTW_8225_ADDR_C_MAGIC, URTW_8225_ADDR_C_DATA_MAGIC1);
	else
		urtw_8225_write(sc,
		    URTW_8225_ADDR_C_MAGIC, URTW_8225_ADDR_C_DATA_MAGIC2);

	sens = 6 - sens;
	error = urtw_8225_setgain(sc, sens);
	if (error)
		goto fail;

	urtw_8187_write_phy_cck(sc, 0x41, urtw_8225_threshold[sens]);

fail:
	return (error);
}