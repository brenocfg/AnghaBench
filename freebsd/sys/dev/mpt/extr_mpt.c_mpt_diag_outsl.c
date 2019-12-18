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
typedef  int /*<<< orphan*/  uint32_t ;
struct mpt_softc {int /*<<< orphan*/  dev; scalar_t__ is_sas; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPT_OFFSET_DIAG_ADDR ; 
 int /*<<< orphan*/  MPT_OFFSET_DIAG_DATA ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  mpt_pio_write (struct mpt_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_enable_io (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roundup2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_diag_outsl(struct mpt_softc *mpt, uint32_t addr,
	       uint32_t *data, bus_size_t len)
{
	uint32_t *data_end;

	data_end = data + (roundup2(len, sizeof(uint32_t)) / 4);
	if (mpt->is_sas) {
		pci_enable_io(mpt->dev, SYS_RES_IOPORT);
	}
	mpt_pio_write(mpt, MPT_OFFSET_DIAG_ADDR, addr);
	while (data != data_end) {
		mpt_pio_write(mpt, MPT_OFFSET_DIAG_DATA, *data);
		data++;
	}
	if (mpt->is_sas) {
		pci_disable_io(mpt->dev, SYS_RES_IOPORT);
	}
}