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
struct TYPE_2__ {int dma_rd_err; int over_fetch_err; int cam_inval_abort; int cam_hard_err; } ;
union lbc_int_ena_w1s {unsigned long long value; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u64 ;
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LBC_ELM_VF1_64_INT_ENA_W1S ; 
 int /*<<< orphan*/  LBC_ELM_VF65_128_INT_ENA_W1S ; 
 int /*<<< orphan*/  LBC_INT_ENA_W1S ; 
 int /*<<< orphan*/  LBC_PLM_VF1_64_INT_ENA_W1S ; 
 int /*<<< orphan*/  LBC_PLM_VF65_128_INT_ENA_W1S ; 
 int /*<<< orphan*/  invalidate_lbc (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_write_csr (struct nitrox_device*,int /*<<< orphan*/ ,unsigned long long) ; 

void nitrox_config_lbc_unit(struct nitrox_device *ndev)
{
	union lbc_int_ena_w1s lbc_int_ena;
	u64 offset;

	invalidate_lbc(ndev);

	/* enable interrupts */
	offset = LBC_INT_ENA_W1S;
	lbc_int_ena.value = 0;
	lbc_int_ena.s.dma_rd_err = 1;
	lbc_int_ena.s.over_fetch_err = 1;
	lbc_int_ena.s.cam_inval_abort = 1;
	lbc_int_ena.s.cam_hard_err = 1;
	nitrox_write_csr(ndev, offset, lbc_int_ena.value);

	offset = LBC_PLM_VF1_64_INT_ENA_W1S;
	nitrox_write_csr(ndev, offset, (~0ULL));
	offset = LBC_PLM_VF65_128_INT_ENA_W1S;
	nitrox_write_csr(ndev, offset, (~0ULL));

	offset = LBC_ELM_VF1_64_INT_ENA_W1S;
	nitrox_write_csr(ndev, offset, (~0ULL));
	offset = LBC_ELM_VF65_128_INT_ENA_W1S;
	nitrox_write_csr(ndev, offset, (~0ULL));
}