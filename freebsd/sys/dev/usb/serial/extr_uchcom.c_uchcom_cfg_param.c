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
struct ucom_softc {struct uchcom_softc* sc_parent; } ;
struct uchcom_softc {scalar_t__ sc_version; } ;
struct termios {int /*<<< orphan*/  c_ospeed; } ;

/* Variables and functions */
 int UCHCOM_LCR1_CS8 ; 
 int UCHCOM_LCR1_RX ; 
 int UCHCOM_LCR1_TX ; 
 int /*<<< orphan*/  UCHCOM_REG_LCR1 ; 
 int /*<<< orphan*/  UCHCOM_REG_LCR2 ; 
 int /*<<< orphan*/  UCHCOM_REQ_RESET ; 
 scalar_t__ UCHCOM_VER_30 ; 
 int /*<<< orphan*/  uchcom_ctrl_write (struct uchcom_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  uchcom_get_version (struct uchcom_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uchcom_read_reg (struct uchcom_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uchcom_set_baudrate (struct uchcom_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uchcom_set_dtr_rts (struct uchcom_softc*) ; 
 int /*<<< orphan*/  uchcom_update_status (struct uchcom_softc*) ; 
 int /*<<< orphan*/  uchcom_write_reg (struct uchcom_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
uchcom_cfg_param(struct ucom_softc *ucom, struct termios *t)
{
	struct uchcom_softc *sc = ucom->sc_parent;

	uchcom_get_version(sc, NULL);
	uchcom_ctrl_write(sc, UCHCOM_REQ_RESET, 0, 0);
	uchcom_set_baudrate(sc, t->c_ospeed);
	if (sc->sc_version < UCHCOM_VER_30) {
		uchcom_read_reg(sc, UCHCOM_REG_LCR1, NULL,
		    UCHCOM_REG_LCR2, NULL);
		uchcom_write_reg(sc, UCHCOM_REG_LCR1, 0x50,
		    UCHCOM_REG_LCR2, 0x00);
	} else {
		/*
		 * Set up line control:
		 * - enable transmit and receive
		 * - set 8n1 mode
		 * To do: support other sizes, parity, stop bits.
		 */
		uchcom_write_reg(sc,
		    UCHCOM_REG_LCR1,
		    UCHCOM_LCR1_RX | UCHCOM_LCR1_TX | UCHCOM_LCR1_CS8,
		    UCHCOM_REG_LCR2, 0x00);
	}
	uchcom_update_status(sc);
	uchcom_ctrl_write(sc, UCHCOM_REQ_RESET, 0x501f, 0xd90a);
	uchcom_set_baudrate(sc, t->c_ospeed);
	uchcom_set_dtr_rts(sc);
	uchcom_update_status(sc);
}