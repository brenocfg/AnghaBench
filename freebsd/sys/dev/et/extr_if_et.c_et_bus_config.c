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
typedef  scalar_t__ uint16_t ;
struct et_softc {int sc_flags; int /*<<< orphan*/  dev; scalar_t__ sc_expcap; } ;

/* Variables and functions */
 int ENXIO ; 
 int ET_FLAG_PCIE ; 
 int ET_PCIM_EEPROM_STATUS_ERROR ; 
 scalar_t__ ET_PCIR_ACK_LATENCY ; 
 scalar_t__ ET_PCIR_EEPROM_STATUS ; 
 scalar_t__ ET_PCIR_L0S_L1_LATENCY ; 
 scalar_t__ ET_PCIR_REPLAY_TIMER ; 
 scalar_t__ ET_PCIV_ACK_LATENCY_128 ; 
 scalar_t__ ET_PCIV_ACK_LATENCY_256 ; 
#define  ET_PCIV_DEVICE_CAPS_PLSZ_128 129 
#define  ET_PCIV_DEVICE_CAPS_PLSZ_256 128 
 scalar_t__ ET_PCIV_REPLAY_TIMER_128 ; 
 scalar_t__ ET_PCIV_REPLAY_TIMER_256 ; 
 int PCIEM_CAP_MAX_PAYLOAD ; 
 int PCIEM_LINK_CAP_L0S_EXIT ; 
 int PCIEM_LINK_CAP_L1_EXIT ; 
 scalar_t__ PCIER_DEVICE_CAP ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 void* pci_read_config (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  pci_set_max_read_req (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static int
et_bus_config(struct et_softc *sc)
{
	uint32_t val, max_plsz;
	uint16_t ack_latency, replay_timer;

	/*
	 * Test whether EEPROM is valid
	 * NOTE: Read twice to get the correct value
	 */
	pci_read_config(sc->dev, ET_PCIR_EEPROM_STATUS, 1);
	val = pci_read_config(sc->dev, ET_PCIR_EEPROM_STATUS, 1);
	if (val & ET_PCIM_EEPROM_STATUS_ERROR) {
		device_printf(sc->dev, "EEPROM status error 0x%02x\n", val);
		return (ENXIO);
	}

	/* TODO: LED */

	if ((sc->sc_flags & ET_FLAG_PCIE) == 0)
		return (0);

	/*
	 * Configure ACK latency and replay timer according to
	 * max playload size
	 */
	val = pci_read_config(sc->dev,
	    sc->sc_expcap + PCIER_DEVICE_CAP, 4);
	max_plsz = val & PCIEM_CAP_MAX_PAYLOAD;

	switch (max_plsz) {
	case ET_PCIV_DEVICE_CAPS_PLSZ_128:
		ack_latency = ET_PCIV_ACK_LATENCY_128;
		replay_timer = ET_PCIV_REPLAY_TIMER_128;
		break;

	case ET_PCIV_DEVICE_CAPS_PLSZ_256:
		ack_latency = ET_PCIV_ACK_LATENCY_256;
		replay_timer = ET_PCIV_REPLAY_TIMER_256;
		break;

	default:
		ack_latency = pci_read_config(sc->dev, ET_PCIR_ACK_LATENCY, 2);
		replay_timer = pci_read_config(sc->dev,
		    ET_PCIR_REPLAY_TIMER, 2);
		device_printf(sc->dev, "ack latency %u, replay timer %u\n",
			      ack_latency, replay_timer);
		break;
	}
	if (ack_latency != 0) {
		pci_write_config(sc->dev, ET_PCIR_ACK_LATENCY, ack_latency, 2);
		pci_write_config(sc->dev, ET_PCIR_REPLAY_TIMER, replay_timer,
		    2);
	}

	/*
	 * Set L0s and L1 latency timer to 2us
	 */
	val = pci_read_config(sc->dev, ET_PCIR_L0S_L1_LATENCY, 4);
	val &= ~(PCIEM_LINK_CAP_L0S_EXIT | PCIEM_LINK_CAP_L1_EXIT);
	/* L0s exit latency : 2us */
	val |= 0x00005000;
	/* L1 exit latency : 2us */
	val |= 0x00028000;
	pci_write_config(sc->dev, ET_PCIR_L0S_L1_LATENCY, val, 4);

	/*
	 * Set max read request size to 2048 bytes
	 */
	pci_set_max_read_req(sc->dev, 2048);

	return (0);
}