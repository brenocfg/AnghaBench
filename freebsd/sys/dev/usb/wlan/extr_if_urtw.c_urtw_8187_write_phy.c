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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct urtw_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_PHY_MAGIC1 ; 
 int /*<<< orphan*/  URTW_PHY_MAGIC2 ; 
 int /*<<< orphan*/  URTW_PHY_MAGIC3 ; 
 int /*<<< orphan*/  URTW_PHY_MAGIC4 ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urtw_8187_write_phy(struct urtw_softc *sc, uint8_t addr, uint32_t data)
{
	uint32_t phyw;
	usb_error_t error;

	phyw = ((data << 8) | (addr | 0x80));
	urtw_write8_m(sc, URTW_PHY_MAGIC4, ((phyw & 0xff000000) >> 24));
	urtw_write8_m(sc, URTW_PHY_MAGIC3, ((phyw & 0x00ff0000) >> 16));
	urtw_write8_m(sc, URTW_PHY_MAGIC2, ((phyw & 0x0000ff00) >> 8));
	urtw_write8_m(sc, URTW_PHY_MAGIC1, ((phyw & 0x000000ff)));
	usb_pause_mtx(&sc->sc_mtx, 1);
fail:
	return (error);
}