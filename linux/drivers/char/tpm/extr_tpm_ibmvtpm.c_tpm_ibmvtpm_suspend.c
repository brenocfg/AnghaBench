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
struct device {int dummy; } ;
struct tpm_chip {struct device dev; } ;
struct ibmvtpm_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int H_SUCCESS ; 
 int /*<<< orphan*/  IBMVTPM_VALID_CMD ; 
 int /*<<< orphan*/  VTPM_PREPARE_TO_SUSPEND ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 void* dev_get_drvdata (struct device*) ; 
 int ibmvtpm_send_crq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_ibmvtpm_suspend(struct device *dev)
{
	struct tpm_chip *chip = dev_get_drvdata(dev);
	struct ibmvtpm_dev *ibmvtpm = dev_get_drvdata(&chip->dev);
	int rc = 0;

	rc = ibmvtpm_send_crq(ibmvtpm->vdev,
			IBMVTPM_VALID_CMD, VTPM_PREPARE_TO_SUSPEND, 0, 0);
	if (rc != H_SUCCESS)
		dev_err(ibmvtpm->dev,
			"tpm_ibmvtpm_suspend failed rc=%d\n", rc);

	return rc;
}