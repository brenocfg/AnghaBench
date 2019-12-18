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
struct urtw_softc {int sc_flags; int sc_tx_retry; int sc_rts_retry; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_CMD ; 
 int URTW_CMD_TX_ENABLE ; 
 int /*<<< orphan*/  URTW_CW_CONF ; 
 int URTW_CW_CONF_PERPACKET_CW ; 
 int URTW_CW_CONF_PERPACKET_RETRY ; 
 int /*<<< orphan*/  URTW_MSR ; 
 int URTW_MSR_LINK_ENEDCA ; 
 int URTW_RTL8187B ; 
 int /*<<< orphan*/  URTW_TX_AGC_CTL ; 
 int URTW_TX_AGC_CTL_FEEDBACK_ANT ; 
 int URTW_TX_AGC_CTL_PERPACKET_ANTSEL ; 
 int URTW_TX_AGC_CTL_PERPACKET_GAIN ; 
 int /*<<< orphan*/  URTW_TX_CONF ; 
 int URTW_TX_CWMIN ; 
 int URTW_TX_DISCW ; 
 int URTW_TX_DISREQQSIZE ; 
 int URTW_TX_DPRETRY_MASK ; 
 int URTW_TX_DPRETRY_SHIFT ; 
 int URTW_TX_HW_SEQNUM ; 
 int URTW_TX_LOOPBACK_MASK ; 
 int URTW_TX_LOOPBACK_NONE ; 
 int URTW_TX_MXDMA_2048 ; 
 int URTW_TX_MXDMA_MASK ; 
 int URTW_TX_NOCRC ; 
 int URTW_TX_NOICV ; 
 int URTW_TX_RTSRETRY_MASK ; 
 int URTW_TX_RTSRETRY_SHIFT ; 
 int URTW_TX_SWPLCPLEN ; 
 int /*<<< orphan*/  urtw_read32_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_read8_m (struct urtw_softc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  urtw_write32_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  urtw_write8_m (struct urtw_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static usb_error_t
urtw_tx_enable(struct urtw_softc *sc)
{
	uint8_t data8;
	uint32_t data;
	usb_error_t error;

	if (sc->sc_flags & URTW_RTL8187B) {
		urtw_read32_m(sc, URTW_TX_CONF, &data);
		data &= ~URTW_TX_LOOPBACK_MASK;
		data &= ~(URTW_TX_DPRETRY_MASK | URTW_TX_RTSRETRY_MASK);
		data &= ~(URTW_TX_NOCRC | URTW_TX_MXDMA_MASK);
		data &= ~URTW_TX_SWPLCPLEN;
		data |= URTW_TX_HW_SEQNUM | URTW_TX_DISREQQSIZE |
		    (7 << 8) |	/* short retry limit */
		    (7 << 0) |	/* long retry limit */
		    (7 << 21);	/* MAX TX DMA */
		urtw_write32_m(sc, URTW_TX_CONF, data);

		urtw_read8_m(sc, URTW_MSR, &data8);
		data8 |= URTW_MSR_LINK_ENEDCA;
		urtw_write8_m(sc, URTW_MSR, data8);
		return (error);
	}

	urtw_read8_m(sc, URTW_CW_CONF, &data8);
	data8 &= ~(URTW_CW_CONF_PERPACKET_CW | URTW_CW_CONF_PERPACKET_RETRY);
	urtw_write8_m(sc, URTW_CW_CONF, data8);

	urtw_read8_m(sc, URTW_TX_AGC_CTL, &data8);
	data8 &= ~URTW_TX_AGC_CTL_PERPACKET_GAIN;
	data8 &= ~URTW_TX_AGC_CTL_PERPACKET_ANTSEL;
	data8 &= ~URTW_TX_AGC_CTL_FEEDBACK_ANT;
	urtw_write8_m(sc, URTW_TX_AGC_CTL, data8);

	urtw_read32_m(sc, URTW_TX_CONF, &data);
	data &= ~URTW_TX_LOOPBACK_MASK;
	data |= URTW_TX_LOOPBACK_NONE;
	data &= ~(URTW_TX_DPRETRY_MASK | URTW_TX_RTSRETRY_MASK);
	data |= sc->sc_tx_retry << URTW_TX_DPRETRY_SHIFT;
	data |= sc->sc_rts_retry << URTW_TX_RTSRETRY_SHIFT;
	data &= ~(URTW_TX_NOCRC | URTW_TX_MXDMA_MASK);
	data |= URTW_TX_MXDMA_2048 | URTW_TX_CWMIN | URTW_TX_DISCW;
	data &= ~URTW_TX_SWPLCPLEN;
	data |= URTW_TX_NOICV;
	urtw_write32_m(sc, URTW_TX_CONF, data);

	urtw_read8_m(sc, URTW_CMD, &data8);
	urtw_write8_m(sc, URTW_CMD, data8 | URTW_CMD_TX_ENABLE);
fail:
	return (error);
}