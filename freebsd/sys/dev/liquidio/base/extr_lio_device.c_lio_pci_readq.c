#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  pci_win_rd_data; int /*<<< orphan*/  pci_win_rd_addr_lo; int /*<<< orphan*/  pci_win_rd_addr_hi; } ;
struct octeon_device {scalar_t__ chip_id; int /*<<< orphan*/  pci_win_lock; TYPE_1__ reg_list; } ;

/* Variables and functions */
 scalar_t__ LIO_CN23XX_PF_VID ; 
 int lio_read_csr32 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,int volatile) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

uint64_t
lio_pci_readq(struct octeon_device *oct, uint64_t addr)
{
	uint64_t		val64;
	volatile uint32_t	val32, addrhi;

	mtx_lock(&oct->pci_win_lock);

	/*
	 * The windowed read happens when the LSB of the addr is written.
	 * So write MSB first
	 */
	addrhi = (addr >> 32);
	if (oct->chip_id == LIO_CN23XX_PF_VID)
		addrhi |= 0x00060000;
	lio_write_csr32(oct, oct->reg_list.pci_win_rd_addr_hi, addrhi);

	/* Read back to preserve ordering of writes */
	val32 = lio_read_csr32(oct, oct->reg_list.pci_win_rd_addr_hi);

	lio_write_csr32(oct, oct->reg_list.pci_win_rd_addr_lo,
			addr & 0xffffffff);
	val32 = lio_read_csr32(oct, oct->reg_list.pci_win_rd_addr_lo);

	val64 = lio_read_csr64(oct, oct->reg_list.pci_win_rd_data);

	mtx_unlock(&oct->pci_win_lock);

	return (val64);
}