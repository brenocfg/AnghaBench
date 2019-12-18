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
struct ntb_softc {scalar_t__ conn_type; unsigned long long db_count; unsigned long long db_valid_mask; int /*<<< orphan*/  heartbeat_timer; int /*<<< orphan*/  device; int /*<<< orphan*/ * xlat_reg; int /*<<< orphan*/ * peer_reg; int /*<<< orphan*/ * self_reg; int /*<<< orphan*/ * reg; int /*<<< orphan*/  db_vec_shift; int /*<<< orphan*/  db_vec_count; int /*<<< orphan*/  spad_count; } ;

/* Variables and functions */
 unsigned long long ATOM_DB_COUNT ; 
 int /*<<< orphan*/  ATOM_DB_MSIX_VECTOR_COUNT ; 
 int /*<<< orphan*/  ATOM_DB_MSIX_VECTOR_SHIFT ; 
 int /*<<< orphan*/  ATOM_SPAD_COUNT ; 
 int /*<<< orphan*/  ATOM_SPCICMD_OFFSET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NTB_CONN_B2B ; 
 int /*<<< orphan*/  NTB_SPEED_AUTO ; 
 int /*<<< orphan*/  NTB_WIDTH_AUTO ; 
 int PCIM_CMD_BUSMASTEREN ; 
 int PCIM_CMD_MEMEN ; 
 int /*<<< orphan*/  atom_b2b_reg ; 
 int /*<<< orphan*/  atom_link_hb ; 
 int /*<<< orphan*/  atom_pri_reg ; 
 int /*<<< orphan*/  atom_reg ; 
 int /*<<< orphan*/  atom_sec_xlat ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ntb_softc*) ; 
 int /*<<< orphan*/  configure_atom_secondary_side_bars (struct ntb_softc*) ; 
 int intel_ntb_init_isr (struct ntb_softc*) ; 
 int /*<<< orphan*/  intel_ntb_link_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_reg_write (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
intel_ntb_atom_init_dev(struct ntb_softc *ntb)
{
	int error;

	KASSERT(ntb->conn_type == NTB_CONN_B2B,
	    ("Unsupported NTB configuration (%d)\n", ntb->conn_type));

	ntb->spad_count		 = ATOM_SPAD_COUNT;
	ntb->db_count		 = ATOM_DB_COUNT;
	ntb->db_vec_count	 = ATOM_DB_MSIX_VECTOR_COUNT;
	ntb->db_vec_shift	 = ATOM_DB_MSIX_VECTOR_SHIFT;
	ntb->db_valid_mask	 = (1ull << ntb->db_count) - 1;

	ntb->reg = &atom_reg;
	ntb->self_reg = &atom_pri_reg;
	ntb->peer_reg = &atom_b2b_reg;
	ntb->xlat_reg = &atom_sec_xlat;

	/*
	 * FIXME - MSI-X bug on early Atom HW, remove once internal issue is
	 * resolved.  Mask transaction layer internal parity errors.
	 */
	pci_write_config(ntb->device, 0xFC, 0x4, 4);

	configure_atom_secondary_side_bars(ntb);

	/* Enable Bus Master and Memory Space on the secondary side */
	intel_ntb_reg_write(2, ATOM_SPCICMD_OFFSET,
	    PCIM_CMD_MEMEN | PCIM_CMD_BUSMASTEREN);

	error = intel_ntb_init_isr(ntb);
	if (error != 0)
		return (error);

	/* Initiate PCI-E link training */
	intel_ntb_link_enable(ntb->device, NTB_SPEED_AUTO, NTB_WIDTH_AUTO);

	callout_reset(&ntb->heartbeat_timer, 0, atom_link_hb, ntb);

	return (0);
}