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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  pci_win_wr_data_lo; int /*<<< orphan*/  pci_win_wr_data_hi; int /*<<< orphan*/  pci_win_wr_addr; } ;
struct octeon_device {int /*<<< orphan*/  pci_win_lock; TYPE_1__ reg_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  lio_read_csr32 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
lio_pci_writeq(struct octeon_device *oct, uint64_t val, uint64_t addr)
{
	volatile uint32_t	val32;

	mtx_lock(&oct->pci_win_lock);

	lio_write_csr64(oct, oct->reg_list.pci_win_wr_addr, addr);

	/* The write happens when the LSB is written. So write MSB first. */
	lio_write_csr32(oct, oct->reg_list.pci_win_wr_data_hi, val >> 32);
	/* Read the MSB to ensure ordering of writes. */
	val32 = lio_read_csr32(oct, oct->reg_list.pci_win_wr_data_hi);

	lio_write_csr32(oct, oct->reg_list.pci_win_wr_data_lo,
			val & 0xffffffff);

	mtx_unlock(&oct->pci_win_lock);
}