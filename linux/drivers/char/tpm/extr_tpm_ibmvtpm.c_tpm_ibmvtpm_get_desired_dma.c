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
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct ibmvtpm_dev {unsigned long rtce_size; } ;

/* Variables and functions */
 unsigned long CRQ_RES_BUF_SIZE ; 
 unsigned long PAGE_SIZE ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long tpm_ibmvtpm_get_desired_dma(struct vio_dev *vdev)
{
	struct tpm_chip *chip = dev_get_drvdata(&vdev->dev);
	struct ibmvtpm_dev *ibmvtpm;

	/*
	 * ibmvtpm initializes at probe time, so the data we are
	 * asking for may not be set yet. Estimate that 4K required
	 * for TCE-mapped buffer in addition to CRQ.
	 */
	if (chip)
		ibmvtpm = dev_get_drvdata(&chip->dev);
	else
		return CRQ_RES_BUF_SIZE + PAGE_SIZE;

	return CRQ_RES_BUF_SIZE + ibmvtpm->rtce_size;
}