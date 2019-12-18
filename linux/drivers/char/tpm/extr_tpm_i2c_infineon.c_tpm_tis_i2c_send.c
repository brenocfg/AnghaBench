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
struct tpm_chip {int /*<<< orphan*/  timeout_c; int /*<<< orphan*/  timeout_b; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  locality; } ;

/* Variables and functions */
 int E2BIG ; 
 int EBUSY ; 
 int EIO ; 
 int ETIME ; 
 scalar_t__ MAX_COUNT_LONG ; 
 int /*<<< orphan*/  SLEEP_DURATION_RESET_HI ; 
 int /*<<< orphan*/  SLEEP_DURATION_RESET_LOW ; 
 int /*<<< orphan*/  TPM_DATA_FIFO (int /*<<< orphan*/ ) ; 
 size_t TPM_I2C_INFINEON_BUFSIZE ; 
 int /*<<< orphan*/  TPM_STS (int /*<<< orphan*/ ) ; 
 int TPM_STS_COMMAND_READY ; 
 int TPM_STS_DATA_EXPECT ; 
 scalar_t__ TPM_STS_GO ; 
 int TPM_STS_VALID ; 
 scalar_t__ get_burstcount (struct tpm_chip*) ; 
 int iic_tpm_write (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  release_locality (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ request_locality (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 TYPE_1__ tpm_dev ; 
 int /*<<< orphan*/  tpm_tis_i2c_ready (struct tpm_chip*) ; 
 int tpm_tis_i2c_status (struct tpm_chip*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_stat (struct tpm_chip*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tpm_tis_i2c_send(struct tpm_chip *chip, u8 *buf, size_t len)
{
	int rc, status;
	ssize_t burstcnt;
	size_t count = 0;
	u8 retries = 0;
	u8 sts = TPM_STS_GO;

	if (len > TPM_I2C_INFINEON_BUFSIZE)
		return -E2BIG;

	if (request_locality(chip, 0) < 0)
		return -EBUSY;

	status = tpm_tis_i2c_status(chip);
	if ((status & TPM_STS_COMMAND_READY) == 0) {
		tpm_tis_i2c_ready(chip);
		if (wait_for_stat
		    (chip, TPM_STS_COMMAND_READY,
		     chip->timeout_b, &status) < 0) {
			rc = -ETIME;
			goto out_err;
		}
	}

	while (count < len - 1) {
		burstcnt = get_burstcount(chip);

		/* burstcnt < 0 = TPM is busy */
		if (burstcnt < 0)
			return burstcnt;

		if (burstcnt > (len - 1 - count))
			burstcnt = len - 1 - count;

		rc = iic_tpm_write(TPM_DATA_FIFO(tpm_dev.locality),
				   &(buf[count]), burstcnt);
		if (rc == 0)
			count += burstcnt;
		else if (rc < 0)
			retries++;

		/* avoid endless loop in case of broken HW */
		if (retries > MAX_COUNT_LONG) {
			rc = -EIO;
			goto out_err;
		}

		wait_for_stat(chip, TPM_STS_VALID,
			      chip->timeout_c, &status);

		if ((status & TPM_STS_DATA_EXPECT) == 0) {
			rc = -EIO;
			goto out_err;
		}
	}

	/* write last byte */
	iic_tpm_write(TPM_DATA_FIFO(tpm_dev.locality), &(buf[count]), 1);
	wait_for_stat(chip, TPM_STS_VALID, chip->timeout_c, &status);
	if ((status & TPM_STS_DATA_EXPECT) != 0) {
		rc = -EIO;
		goto out_err;
	}

	/* go and do it */
	iic_tpm_write(TPM_STS(tpm_dev.locality), &sts, 1);

	return 0;
out_err:
	tpm_tis_i2c_ready(chip);
	/* The TPM needs some time to clean up here,
	 * so we sleep rather than keeping the bus busy
	 */
	usleep_range(SLEEP_DURATION_RESET_LOW, SLEEP_DURATION_RESET_HI);
	release_locality(chip, tpm_dev.locality, 0);
	return rc;
}