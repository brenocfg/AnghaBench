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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct tpm_tis_data {int /*<<< orphan*/  int_queue; } ;
struct tpm_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  timeout_c; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EIO ; 
 int ETIME ; 
 size_t TPM_HEADER_SIZE ; 
 int TPM_STS_DATA_AVAIL ; 
 int /*<<< orphan*/  TPM_STS_VALID ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int recv_data (struct tpm_chip*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  tpm_tis_ready (struct tpm_chip*) ; 
 int tpm_tis_status (struct tpm_chip*) ; 
 scalar_t__ wait_for_tpm_stat (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tpm_tis_recv(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	int size = 0;
	int status;
	u32 expected;

	if (count < TPM_HEADER_SIZE) {
		size = -EIO;
		goto out;
	}

	size = recv_data(chip, buf, TPM_HEADER_SIZE);
	/* read first 10 bytes, including tag, paramsize, and result */
	if (size < TPM_HEADER_SIZE) {
		dev_err(&chip->dev, "Unable to read header\n");
		goto out;
	}

	expected = be32_to_cpu(*(__be32 *) (buf + 2));
	if (expected > count || expected < TPM_HEADER_SIZE) {
		size = -EIO;
		goto out;
	}

	size += recv_data(chip, &buf[TPM_HEADER_SIZE],
			  expected - TPM_HEADER_SIZE);
	if (size < expected) {
		dev_err(&chip->dev, "Unable to read remainder of result\n");
		size = -ETIME;
		goto out;
	}

	if (wait_for_tpm_stat(chip, TPM_STS_VALID, chip->timeout_c,
				&priv->int_queue, false) < 0) {
		size = -ETIME;
		goto out;
	}
	status = tpm_tis_status(chip);
	if (status & TPM_STS_DATA_AVAIL) {	/* retry? */
		dev_err(&chip->dev, "Error left over data\n");
		size = -EIO;
		goto out;
	}

out:
	tpm_tis_ready(chip);
	return size;
}