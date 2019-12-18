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
struct device {int dummy; } ;
struct crb_priv {scalar_t__ sm; TYPE_1__* regs_t; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctrl_req; } ;

/* Variables and functions */
 scalar_t__ ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC ; 
 scalar_t__ ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD ; 
 scalar_t__ ACPI_TPM2_START_METHOD ; 
 int /*<<< orphan*/  CRB_CTRL_REQ_GO_IDLE ; 
 int ETIME ; 
 int /*<<< orphan*/  TPM2_TIMEOUT_C ; 
 int /*<<< orphan*/  crb_wait_for_reg_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __crb_go_idle(struct device *dev, struct crb_priv *priv)
{
	if ((priv->sm == ACPI_TPM2_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_START_METHOD) ||
	    (priv->sm == ACPI_TPM2_COMMAND_BUFFER_WITH_ARM_SMC))
		return 0;

	iowrite32(CRB_CTRL_REQ_GO_IDLE, &priv->regs_t->ctrl_req);

	if (!crb_wait_for_reg_32(&priv->regs_t->ctrl_req,
				 CRB_CTRL_REQ_GO_IDLE/* mask */,
				 0, /* value */
				 TPM2_TIMEOUT_C)) {
		dev_warn(dev, "goIdle timed out\n");
		return -ETIME;
	}

	return 0;
}