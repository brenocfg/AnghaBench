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
struct otus_softc {int dummy; } ;

/* Variables and functions */
 int AR_GPIO_REG_PORT_DATA ; 
 int AR_GPIO_REG_PORT_TYPE ; 
 int AR_MAC_REG_ACK_EXTENSION ; 
 int AR_MAC_REG_ACK_TPC ; 
 int AR_MAC_REG_AMPDU_FACTOR ; 
 int AR_MAC_REG_AMPDU_RX_THRESH ; 
 int AR_MAC_REG_BACKOFF_PROTECT ; 
 int AR_MAC_REG_BASIC_RATE ; 
 int AR_MAC_REG_BCN_HT1 ; 
 int AR_MAC_REG_EIFS_AND_SIFS ; 
 int AR_MAC_REG_ENCRYPTION ; 
 int AR_MAC_REG_FCS_SELECT ; 
 int AR_MAC_REG_MANDATORY_RATE ; 
 int AR_MAC_REG_MISC_680 ; 
 int AR_MAC_REG_RETRY_MAX ; 
 int AR_MAC_REG_RTS_CTS_RATE ; 
 int AR_MAC_REG_RX_PE_DELAY ; 
 int AR_MAC_REG_RX_THRESHOLD ; 
 int AR_MAC_REG_RX_TIMEOUT ; 
 int AR_MAC_REG_SLOT_TIME ; 
 int AR_MAC_REG_TID_CFACK_CFEND_RATE ; 
 int AR_MAC_REG_TXOP_DURATION ; 
 int AR_MAC_REG_TXOP_NOT_ENOUGH_INDICATION ; 
 int AR_MAC_REG_TXRX_MPI ; 
 int AR_PWR_REG_CLOCK_SEL ; 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_set_rx_filter (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_updateedca_locked (struct otus_softc*) ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int,int) ; 
 int otus_write_barrier (struct otus_softc*) ; 

int
otus_init_mac(struct otus_softc *sc)
{
	int error;

	OTUS_LOCK_ASSERT(sc);

	otus_write(sc, AR_MAC_REG_ACK_EXTENSION, 0x40);
	otus_write(sc, AR_MAC_REG_RETRY_MAX, 0);
	otus_write(sc, AR_MAC_REG_RX_THRESHOLD, 0xc1f80);
	otus_write(sc, AR_MAC_REG_RX_PE_DELAY, 0x70);
	otus_write(sc, AR_MAC_REG_EIFS_AND_SIFS, 0xa144000);
	otus_write(sc, AR_MAC_REG_SLOT_TIME, 9 << 10);
	otus_write(sc, AR_MAC_REG_TID_CFACK_CFEND_RATE, 0x19000000);
	/* NAV protects ACK only (in TXOP). */
	otus_write(sc, AR_MAC_REG_TXOP_DURATION, 0x201);
	/* Set beacon Tx power to 0x7. */
	otus_write(sc, AR_MAC_REG_BCN_HT1, 0x8000170);
	otus_write(sc, AR_MAC_REG_BACKOFF_PROTECT, 0x105);
	otus_write(sc, AR_MAC_REG_AMPDU_FACTOR, 0x10000a);

	otus_set_rx_filter(sc);

	otus_write(sc, AR_MAC_REG_BASIC_RATE, 0x150f);
	otus_write(sc, AR_MAC_REG_MANDATORY_RATE, 0x150f);
	otus_write(sc, AR_MAC_REG_RTS_CTS_RATE, 0x10b01bb);
	otus_write(sc, AR_MAC_REG_ACK_TPC, 0x4003c1e);

	/* Enable LED0 and LED1. */
	otus_write(sc, AR_GPIO_REG_PORT_TYPE, 0x3);
	otus_write(sc, AR_GPIO_REG_PORT_DATA, 0x3);
	/* Switch MAC to OTUS interface. */
	otus_write(sc, 0x1c3600, 0x3);
	otus_write(sc, AR_MAC_REG_AMPDU_RX_THRESH, 0xffff);
	otus_write(sc, AR_MAC_REG_MISC_680, 0xf00008);
	/* Disable Rx timeout (workaround). */
	otus_write(sc, AR_MAC_REG_RX_TIMEOUT, 0);

	/* Set USB Rx stream mode maximum frame number to 2. */
	otus_write(sc, 0x1e1110, 0x4);
	/* Set USB Rx stream mode timeout to 10us. */
	otus_write(sc, 0x1e1114, 0x80);

	/* Set clock frequency to 88/80MHz. */
	otus_write(sc, AR_PWR_REG_CLOCK_SEL, 0x73);
	/* Set WLAN DMA interrupt mode: generate intr per packet. */
	otus_write(sc, AR_MAC_REG_TXRX_MPI, 0x110011);
	otus_write(sc, AR_MAC_REG_FCS_SELECT, 0x4);
	otus_write(sc, AR_MAC_REG_TXOP_NOT_ENOUGH_INDICATION, 0x141e0f48);

	/* Disable HW decryption for now. */
	otus_write(sc, AR_MAC_REG_ENCRYPTION, 0x78);

	if ((error = otus_write_barrier(sc)) != 0)
		return error;

	/* Set default EDCA parameters. */
	otus_updateedca_locked(sc);

	return 0;
}