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
struct rtwn_softc {int bcn_check_interval; int /*<<< orphan*/  sc_beacon_unload; int /*<<< orphan*/  sc_beacon_update_end; int /*<<< orphan*/  sc_beacon_update_begin; void* sc_drop_incorrect_tx; int /*<<< orphan*/  sc_set_desc_addr; int /*<<< orphan*/  sc_get_qmap; int /*<<< orphan*/  sc_fw_write_block; void* sc_abort_xfers; int /*<<< orphan*/  sc_reset_lists; int /*<<< orphan*/  sc_tx_start; int /*<<< orphan*/  sc_delay; int /*<<< orphan*/  sc_read_4; int /*<<< orphan*/  sc_read_2; int /*<<< orphan*/  sc_read_1; int /*<<< orphan*/  sc_write_4; int /*<<< orphan*/  sc_write_2; int /*<<< orphan*/  sc_write_1; } ;

/* Variables and functions */
 void* rtwn_nop_softc ; 
 int /*<<< orphan*/  rtwn_pci_beacon_update_begin ; 
 int /*<<< orphan*/  rtwn_pci_beacon_update_end ; 
 int /*<<< orphan*/  rtwn_pci_delay ; 
 int /*<<< orphan*/  rtwn_pci_fw_write_block ; 
 int /*<<< orphan*/  rtwn_pci_get_qmap ; 
 int /*<<< orphan*/  rtwn_pci_read_1 ; 
 int /*<<< orphan*/  rtwn_pci_read_2 ; 
 int /*<<< orphan*/  rtwn_pci_read_4 ; 
 int /*<<< orphan*/  rtwn_pci_reset_beacon_ring ; 
 int /*<<< orphan*/  rtwn_pci_reset_lists ; 
 int /*<<< orphan*/  rtwn_pci_set_desc_addr ; 
 int /*<<< orphan*/  rtwn_pci_tx_start ; 
 int /*<<< orphan*/  rtwn_pci_write_1 ; 
 int /*<<< orphan*/  rtwn_pci_write_2 ; 
 int /*<<< orphan*/  rtwn_pci_write_4 ; 

__attribute__((used)) static void
rtwn_pci_attach_methods(struct rtwn_softc *sc)
{
	sc->sc_write_1		= rtwn_pci_write_1;
	sc->sc_write_2		= rtwn_pci_write_2;
	sc->sc_write_4		= rtwn_pci_write_4;
	sc->sc_read_1		= rtwn_pci_read_1;
	sc->sc_read_2		= rtwn_pci_read_2;
	sc->sc_read_4		= rtwn_pci_read_4;
	sc->sc_delay		= rtwn_pci_delay;
	sc->sc_tx_start		= rtwn_pci_tx_start;
	sc->sc_reset_lists	= rtwn_pci_reset_lists;
	sc->sc_abort_xfers	= rtwn_nop_softc;
	sc->sc_fw_write_block	= rtwn_pci_fw_write_block;
	sc->sc_get_qmap		= rtwn_pci_get_qmap;
	sc->sc_set_desc_addr	= rtwn_pci_set_desc_addr;
	sc->sc_drop_incorrect_tx = rtwn_nop_softc;
	sc->sc_beacon_update_begin = rtwn_pci_beacon_update_begin;
	sc->sc_beacon_update_end = rtwn_pci_beacon_update_end;
	sc->sc_beacon_unload	= rtwn_pci_reset_beacon_ring;

	sc->bcn_check_interval	= 25000;
}