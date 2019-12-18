#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/  serdes2_xfi_hss_pll; int /*<<< orphan*/  serdes1_xfi_hss_pll; int /*<<< orphan*/  serdes2_xfi_hss_rx; int /*<<< orphan*/  serdes1_xfi_hss_rx; int /*<<< orphan*/  serdes2_xfi_hss_tx; int /*<<< orphan*/  serdes1_xfi_hss_tx; int /*<<< orphan*/  serdes2_xfi_hss_pcs; int /*<<< orphan*/  serdes1_xfi_hss_pcs; int /*<<< orphan*/  serdes2_xfi_train; int /*<<< orphan*/  serdes1_xfi_train; int /*<<< orphan*/  serdes2_xfi_an; int /*<<< orphan*/  serdes1_xfi_an; int /*<<< orphan*/  serdes2_xaui_hss_pcs; int /*<<< orphan*/  serdes1_xaui_hss_pcs; int /*<<< orphan*/  serdes2_xaui_an; int /*<<< orphan*/  serdes1_xaui_an; } ;
typedef  TYPE_1__ qls_mpi_coredump_t ;
struct TYPE_9__ {int pci_func; } ;
typedef  TYPE_2__ qla_host_t ;

/* Variables and functions */
 int Q81_XAUI_POWERED_UP ; 
 int Q81_XFI1_POWERED_UP ; 
 int Q81_XFI2_POWERED_UP ; 
 int /*<<< orphan*/  qls_get_both_serdes (TYPE_2__*,int,int*,int*,int,int) ; 
 int qls_rd_ofunc_serdes_reg (TYPE_2__*,int,int*) ; 
 int qls_rd_serdes_reg (TYPE_2__*,int,int*) ; 

__attribute__((used)) static int
qls_rd_serdes_regs(qla_host_t *ha, qls_mpi_coredump_t *mpi_dump)
{
	int ret;
	uint32_t xfi_d_valid, xfi_ind_valid, xaui_d_valid, xaui_ind_valid;
	uint32_t temp, xaui_reg, i;
	uint32_t *dptr, *indptr;

	xfi_d_valid = xfi_ind_valid = xaui_d_valid = xaui_ind_valid = 0;

	xaui_reg = 0x800;

	ret = qls_rd_ofunc_serdes_reg(ha, xaui_reg, &temp);
	if (ret)
		temp = 0;

	if ((temp & Q81_XAUI_POWERED_UP) == Q81_XAUI_POWERED_UP)
		xaui_ind_valid = 1;

	ret = qls_rd_serdes_reg(ha, xaui_reg, &temp);
	if (ret)
		temp = 0;

	if ((temp & Q81_XAUI_POWERED_UP) == Q81_XAUI_POWERED_UP)
		xaui_d_valid = 1;

	ret = qls_rd_serdes_reg(ha, 0x1E06, &temp);
	if (ret)
		temp = 0;

	if ((temp & Q81_XFI1_POWERED_UP) == Q81_XFI1_POWERED_UP) {

		if (ha->pci_func & 1)
         		xfi_ind_valid = 1; /* NIC 2, so the indirect
						 (NIC1) xfi is up*/
		else
			xfi_d_valid = 1;
	}

	if((temp & Q81_XFI2_POWERED_UP) == Q81_XFI2_POWERED_UP) {

		if(ha->pci_func & 1)
			xfi_d_valid = 1; /* NIC 2, so the indirect (NIC1)
						xfi is up */
		else
			xfi_ind_valid = 1;
	}

	if (ha->pci_func & 1) {
		dptr = (uint32_t *)(&mpi_dump->serdes2_xaui_an);
		indptr = (uint32_t *)(&mpi_dump->serdes1_xaui_an);
	} else {
		dptr = (uint32_t *)(&mpi_dump->serdes1_xaui_an);
		indptr = (uint32_t *)(&mpi_dump->serdes2_xaui_an);
	}

	for (i = 0; i <= 0x000000034; i += 4, dptr ++, indptr ++) {
		qls_get_both_serdes(ha, i, dptr, indptr,
			xaui_d_valid, xaui_ind_valid);
	}

	if (ha->pci_func & 1) {
		dptr = (uint32_t *)(&mpi_dump->serdes2_xaui_hss_pcs);
		indptr = (uint32_t *)(&mpi_dump->serdes1_xaui_hss_pcs);
	} else {
		dptr = (uint32_t *)(&mpi_dump->serdes1_xaui_hss_pcs);
		indptr = (uint32_t *)(&mpi_dump->serdes2_xaui_hss_pcs);
	}

	for (i = 0x800; i <= 0x880; i += 4, dptr ++, indptr ++) {
		qls_get_both_serdes(ha, i, dptr, indptr,
			xaui_d_valid, xaui_ind_valid);
	}

	if (ha->pci_func & 1) {
		dptr = (uint32_t *)(&mpi_dump->serdes2_xfi_an);
		indptr = (uint32_t *)(&mpi_dump->serdes1_xfi_an);
	} else {
		dptr = (uint32_t *)(&mpi_dump->serdes1_xfi_an);
		indptr = (uint32_t *)(&mpi_dump->serdes2_xfi_an);
	}

	for (i = 0x1000; i <= 0x1034; i += 4, dptr ++, indptr ++) {
		qls_get_both_serdes(ha, i, dptr, indptr,
			xfi_d_valid, xfi_ind_valid);
	}

	if (ha->pci_func & 1) {
		dptr = (uint32_t *)(&mpi_dump->serdes2_xfi_train);
		indptr = (uint32_t *)(&mpi_dump->serdes1_xfi_train);
	} else {
		dptr = (uint32_t *)(&mpi_dump->serdes1_xfi_train);
		indptr = (uint32_t *)(&mpi_dump->serdes2_xfi_train);
	}

	for (i = 0x1050; i <= 0x107c; i += 4, dptr ++, indptr ++) {
		qls_get_both_serdes(ha, i, dptr, indptr,
			xfi_d_valid, xfi_ind_valid);
	}

	if (ha->pci_func & 1) {
		dptr = (uint32_t *)(&mpi_dump->serdes2_xfi_hss_pcs);
		indptr = (uint32_t *)(&mpi_dump->serdes1_xfi_hss_pcs);
	} else {
		dptr = (uint32_t *)(&mpi_dump->serdes1_xfi_hss_pcs);
		indptr = (uint32_t *)(&mpi_dump->serdes2_xfi_hss_pcs);
	}

	for (i = 0x1800; i <= 0x1838; i += 4, dptr++, indptr ++) {
		qls_get_both_serdes(ha, i, dptr, indptr,
			xfi_d_valid, xfi_ind_valid);
	}

	if (ha->pci_func & 1) {
		dptr = (uint32_t *)(&mpi_dump->serdes2_xfi_hss_tx);
		indptr = (uint32_t *)(&mpi_dump->serdes1_xfi_hss_tx);
	} else {
		dptr = (uint32_t *)(&mpi_dump->serdes1_xfi_hss_tx);
		indptr = (uint32_t *)(&mpi_dump->serdes2_xfi_hss_tx);
	}

	for (i = 0x1c00; i <= 0x1c1f; i++, dptr ++, indptr ++) {
		qls_get_both_serdes(ha, i, dptr, indptr,
			xfi_d_valid, xfi_ind_valid);
	}

	if (ha->pci_func & 1) {
		dptr = (uint32_t *)(&mpi_dump->serdes2_xfi_hss_rx);
		indptr = (uint32_t *)(&mpi_dump->serdes1_xfi_hss_rx);
	} else {
		dptr = (uint32_t *)(&mpi_dump->serdes1_xfi_hss_rx);
		indptr = (uint32_t *)(&mpi_dump->serdes2_xfi_hss_rx);
	}

	for (i = 0x1c40; i <= 0x1c5f; i++, dptr ++, indptr ++) {
		qls_get_both_serdes(ha, i, dptr, indptr,
			xfi_d_valid, xfi_ind_valid);
	}

	if (ha->pci_func & 1) {
		dptr = (uint32_t *)(&mpi_dump->serdes2_xfi_hss_pll);
		indptr = (uint32_t *)(&mpi_dump->serdes1_xfi_hss_pll);
	} else {
		dptr = (uint32_t *)(&mpi_dump->serdes1_xfi_hss_pll);
		indptr = (uint32_t *)(&mpi_dump->serdes2_xfi_hss_pll);
	}

	for (i = 0x1e00; i <= 0x1e1f; i++, dptr ++, indptr ++) {
		qls_get_both_serdes(ha, i, dptr, indptr,
			xfi_d_valid, xfi_ind_valid);
	}

	return(0);
}