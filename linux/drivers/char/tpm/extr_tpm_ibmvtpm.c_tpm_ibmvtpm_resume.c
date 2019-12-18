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
struct tpm_chip {struct device dev; } ;
struct ibmvtpm_dev {TYPE_1__* vdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  unit_address; } ;

/* Variables and functions */
 int H_BUSY ; 
 int /*<<< orphan*/  H_ENABLE_CRQ ; 
 int H_IN_PROGRESS ; 
 scalar_t__ H_IS_LONG_BUSY (int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* dev_get_drvdata (struct device*) ; 
 int ibmvtpm_crq_send_init (struct ibmvtpm_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int plpar_hcall_norets (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vio_enable_interrupts (TYPE_1__*) ; 

__attribute__((used)) static int tpm_ibmvtpm_resume(struct device *dev)
{
	struct tpm_chip *chip = dev_get_drvdata(dev);
	struct ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	int rc = 0;

	do {
		if (rc)
			msleep(100);
		rc = plpar_hcall_norets(H_ENABLE_CRQ,
					ibmvtpm->vdev->unit_address);
	} while (rc == H_IN_PROGRESS || rc == H_BUSY || H_IS_LONG_BUSY(rc));

	if (rc) {
		dev_err(dev, "Error enabling ibmvtpm rc=%d\n", rc);
		return rc;
	}

	rc = vio_enable_interrupts(ibmvtpm->vdev);
	if (rc) {
		dev_err(dev, "Error vio_enable_interrupts rc=%d\n", rc);
		return rc;
	}

	rc = ibmvtpm_crq_send_init(ibmvtpm);
	if (rc)
		dev_err(dev, "Error send_init rc=%d\n", rc);

	return rc;
}