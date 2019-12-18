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
struct ibmvtpm_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int H_SUCCESS ; 
 int /*<<< orphan*/  INIT_CRQ_COMP_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int ibmvtpm_send_crq_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ibmvtpm_crq_send_init_complete(struct ibmvtpm_dev *ibmvtpm)
{
	int rc;

	rc = ibmvtpm_send_crq_word(ibmvtpm->vdev, INIT_CRQ_COMP_CMD);
	if (rc != H_SUCCESS)
		dev_err(ibmvtpm->dev,
			"ibmvtpm_crq_send_init_complete failed rc=%d\n", rc);

	return rc;
}