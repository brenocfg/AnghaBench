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
struct tpm_chip {int flags; int /*<<< orphan*/  ops_sem; int /*<<< orphan*/ * ops; int /*<<< orphan*/  dev_num; int /*<<< orphan*/  dev; int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM2_SU_CLEAR ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int /*<<< orphan*/  cdev_device_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_nums_idr ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_lock ; 
 int /*<<< orphan*/  idr_replace (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm2_shutdown (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_chip_start (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_chip_stop (struct tpm_chip*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tpm_del_char_device(struct tpm_chip *chip)
{
	cdev_device_del(&chip->cdev, &chip->dev);

	/* Make the chip unavailable. */
	mutex_lock(&idr_lock);
	idr_replace(&dev_nums_idr, NULL, chip->dev_num);
	mutex_unlock(&idr_lock);

	/* Make the driver uncallable. */
	down_write(&chip->ops_sem);
	if (chip->flags & TPM_CHIP_FLAG_TPM2) {
		if (!tpm_chip_start(chip)) {
			tpm2_shutdown(chip, TPM2_SU_CLEAR);
			tpm_chip_stop(chip);
		}
	}
	chip->ops = NULL;
	up_write(&chip->ops_sem);
}