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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct fpga_manager {struct altera_cvp_conf* priv; } ;
struct altera_cvp_conf {TYPE_1__* pci_dev; scalar_t__ sent_packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ALTERA_CVP_V2_SIZE ; 
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int V2_CHECK_CREDIT_US ; 
 int V2_CREDIT_TIMEOUT_US ; 
 int /*<<< orphan*/  VSE_CVP_TX_CREDITS ; 
 int altera_cvp_chk_error (struct fpga_manager*,int) ; 
 int altera_read_config_byte (struct altera_cvp_conf*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int altera_cvp_v2_wait_for_credit(struct fpga_manager *mgr,
					 u32 blocks)
{
	u32 timeout = V2_CREDIT_TIMEOUT_US / V2_CHECK_CREDIT_US;
	struct altera_cvp_conf *conf = mgr->priv;
	int ret;
	u8 val;

	do {
		ret = altera_read_config_byte(conf, VSE_CVP_TX_CREDITS, &val);
		if (ret) {
			dev_err(&conf->pci_dev->dev,
				"Error reading CVP Credit Register\n");
			return ret;
		}

		/* Return if there is space in FIFO */
		if (val - (u8)conf->sent_packets)
			return 0;

		ret = altera_cvp_chk_error(mgr, blocks * ALTERA_CVP_V2_SIZE);
		if (ret) {
			dev_err(&conf->pci_dev->dev,
				"CE Bit error credit reg[0x%x]:sent[0x%x]\n",
				val, conf->sent_packets);
			return -EAGAIN;
		}

		/* Limit the check credit byte traffic */
		usleep_range(V2_CHECK_CREDIT_US, V2_CHECK_CREDIT_US + 1);
	} while (timeout--);

	dev_err(&conf->pci_dev->dev, "Timeout waiting for credit\n");
	return -ETIMEDOUT;
}