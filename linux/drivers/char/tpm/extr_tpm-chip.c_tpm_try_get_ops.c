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
struct tpm_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  ops_sem; int /*<<< orphan*/  tpm_mutex; int /*<<< orphan*/  ops; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int tpm_chip_start (struct tpm_chip*) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int tpm_try_get_ops(struct tpm_chip *chip)
{
	int rc = -EIO;

	get_device(&chip->dev);

	down_read(&chip->ops_sem);
	if (!chip->ops)
		goto out_ops;

	mutex_lock(&chip->tpm_mutex);
	rc = tpm_chip_start(chip);
	if (rc)
		goto out_lock;

	return 0;
out_lock:
	mutex_unlock(&chip->tpm_mutex);
out_ops:
	up_read(&chip->ops_sem);
	put_device(&chip->dev);
	return rc;
}