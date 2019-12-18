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
typedef  size_t u32 ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ETIME ; 
 size_t TPM_HEADER_SIZE ; 
 size_t be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int recv_data (struct tpm_chip*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  release_locality (struct tpm_chip*) ; 
 int /*<<< orphan*/  st33zp24_cancel (struct tpm_chip*) ; 

__attribute__((used)) static int st33zp24_recv(struct tpm_chip *chip, unsigned char *buf,
			    size_t count)
{
	int size = 0;
	u32 expected;

	if (!chip)
		return -EBUSY;

	if (count < TPM_HEADER_SIZE) {
		size = -EIO;
		goto out;
	}

	size = recv_data(chip, buf, TPM_HEADER_SIZE);
	if (size < TPM_HEADER_SIZE) {
		dev_err(&chip->dev, "Unable to read header\n");
		goto out;
	}

	expected = be32_to_cpu(*(__be32 *)(buf + 2));
	if (expected > count || expected < TPM_HEADER_SIZE) {
		size = -EIO;
		goto out;
	}

	size += recv_data(chip, &buf[TPM_HEADER_SIZE],
			expected - TPM_HEADER_SIZE);
	if (size < expected) {
		dev_err(&chip->dev, "Unable to read remainder of result\n");
		size = -ETIME;
	}

out:
	st33zp24_cancel(chip);
	release_locality(chip);
	return size;
}