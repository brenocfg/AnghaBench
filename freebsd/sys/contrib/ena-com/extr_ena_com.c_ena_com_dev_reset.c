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
typedef  int u32 ;
struct TYPE_2__ {int completion_timeout; } ;
struct ena_com_dev {TYPE_1__ admin_queue; scalar_t__ reg_bar; int /*<<< orphan*/  bus; } ;
typedef  enum ena_regs_reset_reason_types { ____Placeholder_ena_regs_reset_reason_types } ena_regs_reset_reason_types ;

/* Variables and functions */
 int ADMIN_CMD_TIMEOUT_US ; 
 int ENA_COM_INVAL ; 
 int ENA_COM_TIMER_EXPIRED ; 
 int ENA_MMIO_READ_TIMEOUT ; 
 int ENA_REGS_CAPS_ADMIN_CMD_TO_MASK ; 
 int ENA_REGS_CAPS_ADMIN_CMD_TO_SHIFT ; 
 int /*<<< orphan*/  ENA_REGS_CAPS_OFF ; 
 int ENA_REGS_CAPS_RESET_TIMEOUT_MASK ; 
 int ENA_REGS_CAPS_RESET_TIMEOUT_SHIFT ; 
 int ENA_REGS_DEV_CTL_DEV_RESET_MASK ; 
 scalar_t__ ENA_REGS_DEV_CTL_OFF ; 
 int ENA_REGS_DEV_CTL_RESET_REASON_MASK ; 
 int ENA_REGS_DEV_CTL_RESET_REASON_SHIFT ; 
 int /*<<< orphan*/  ENA_REGS_DEV_STS_OFF ; 
 int ENA_REGS_DEV_STS_READY_MASK ; 
 int /*<<< orphan*/  ENA_REGS_DEV_STS_RESET_IN_PROGRESS_MASK ; 
 int /*<<< orphan*/  ENA_REG_WRITE32 (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  ena_com_mmio_reg_read_request_write_dev_addr (struct ena_com_dev*) ; 
 int ena_com_reg_bar_read32 (struct ena_com_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 
 scalar_t__ unlikely (int) ; 
 int wait_for_reset_state (struct ena_com_dev*,int,int /*<<< orphan*/ ) ; 

int ena_com_dev_reset(struct ena_com_dev *ena_dev,
		      enum ena_regs_reset_reason_types reset_reason)
{
	u32 stat, timeout, cap, reset_val;
	int rc;

	stat = ena_com_reg_bar_read32(ena_dev, ENA_REGS_DEV_STS_OFF);
	cap = ena_com_reg_bar_read32(ena_dev, ENA_REGS_CAPS_OFF);

	if (unlikely((stat == ENA_MMIO_READ_TIMEOUT) ||
		     (cap == ENA_MMIO_READ_TIMEOUT))) {
		ena_trc_err("Reg read32 timeout occurred\n");
		return ENA_COM_TIMER_EXPIRED;
	}

	if ((stat & ENA_REGS_DEV_STS_READY_MASK) == 0) {
		ena_trc_err("Device isn't ready, can't reset device\n");
		return ENA_COM_INVAL;
	}

	timeout = (cap & ENA_REGS_CAPS_RESET_TIMEOUT_MASK) >>
			ENA_REGS_CAPS_RESET_TIMEOUT_SHIFT;
	if (timeout == 0) {
		ena_trc_err("Invalid timeout value\n");
		return ENA_COM_INVAL;
	}

	/* start reset */
	reset_val = ENA_REGS_DEV_CTL_DEV_RESET_MASK;
	reset_val |= (reset_reason << ENA_REGS_DEV_CTL_RESET_REASON_SHIFT) &
			ENA_REGS_DEV_CTL_RESET_REASON_MASK;
	ENA_REG_WRITE32(ena_dev->bus, reset_val, ena_dev->reg_bar + ENA_REGS_DEV_CTL_OFF);

	/* Write again the MMIO read request address */
	ena_com_mmio_reg_read_request_write_dev_addr(ena_dev);

	rc = wait_for_reset_state(ena_dev, timeout,
				  ENA_REGS_DEV_STS_RESET_IN_PROGRESS_MASK);
	if (rc != 0) {
		ena_trc_err("Reset indication didn't turn on\n");
		return rc;
	}

	/* reset done */
	ENA_REG_WRITE32(ena_dev->bus, 0, ena_dev->reg_bar + ENA_REGS_DEV_CTL_OFF);
	rc = wait_for_reset_state(ena_dev, timeout, 0);
	if (rc != 0) {
		ena_trc_err("Reset indication didn't turn off\n");
		return rc;
	}

	timeout = (cap & ENA_REGS_CAPS_ADMIN_CMD_TO_MASK) >>
		ENA_REGS_CAPS_ADMIN_CMD_TO_SHIFT;
	if (timeout)
		/* the resolution of timeout reg is 100ms */
		ena_dev->admin_queue.completion_timeout = timeout * 100000;
	else
		ena_dev->admin_queue.completion_timeout = ADMIN_CMD_TIMEOUT_US;

	return 0;
}