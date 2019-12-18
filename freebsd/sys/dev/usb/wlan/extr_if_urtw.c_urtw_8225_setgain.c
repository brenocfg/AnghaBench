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
typedef  int /*<<< orphan*/  usb_error_t ;
struct urtw_softc {int dummy; } ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  urtw_8187_write_phy_ofdm (struct urtw_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * urtw_8225_gain ; 

__attribute__((used)) static usb_error_t
urtw_8225_setgain(struct urtw_softc *sc, int16_t gain)
{
	usb_error_t error;

	urtw_8187_write_phy_ofdm(sc, 0x0d, urtw_8225_gain[gain * 4]);
	urtw_8187_write_phy_ofdm(sc, 0x1b, urtw_8225_gain[gain * 4 + 2]);
	urtw_8187_write_phy_ofdm(sc, 0x1d, urtw_8225_gain[gain * 4 + 3]);
	urtw_8187_write_phy_ofdm(sc, 0x23, urtw_8225_gain[gain * 4 + 1]);
fail:
	return (error);
}