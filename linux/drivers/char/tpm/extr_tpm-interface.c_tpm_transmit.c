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
typedef  scalar_t__ u32 ;
struct tpm_header {int /*<<< orphan*/  return_code; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  save ;

/* Variables and functions */
 scalar_t__ TPM2_CC_SELF_TEST ; 
 unsigned int TPM2_DURATION_LONG ; 
 unsigned int TPM2_DURATION_SHORT ; 
 scalar_t__ TPM2_RC_RETRY ; 
 scalar_t__ TPM2_RC_TESTING ; 
 int /*<<< orphan*/  TPM_HEADER_SIZE ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 
 size_t min (int,size_t) ; 
 int /*<<< orphan*/  tpm_msleep (unsigned int) ; 
 scalar_t__ tpm_try_transmit (struct tpm_chip*,int /*<<< orphan*/ *,size_t) ; 

ssize_t tpm_transmit(struct tpm_chip *chip, u8 *buf, size_t bufsiz)
{
	struct tpm_header *header = (struct tpm_header *)buf;
	/* space for header and handles */
	u8 save[TPM_HEADER_SIZE + 3*sizeof(u32)];
	unsigned int delay_msec = TPM2_DURATION_SHORT;
	u32 rc = 0;
	ssize_t ret;
	const size_t save_size = min(sizeof(save), bufsiz);
	/* the command code is where the return code will be */
	u32 cc = be32_to_cpu(header->return_code);

	/*
	 * Subtlety here: if we have a space, the handles will be
	 * transformed, so when we restore the header we also have to
	 * restore the handles.
	 */
	memcpy(save, buf, save_size);

	for (;;) {
		ret = tpm_try_transmit(chip, buf, bufsiz);
		if (ret < 0)
			break;
		rc = be32_to_cpu(header->return_code);
		if (rc != TPM2_RC_RETRY && rc != TPM2_RC_TESTING)
			break;
		/*
		 * return immediately if self test returns test
		 * still running to shorten boot time.
		 */
		if (rc == TPM2_RC_TESTING && cc == TPM2_CC_SELF_TEST)
			break;

		if (delay_msec > TPM2_DURATION_LONG) {
			if (rc == TPM2_RC_RETRY)
				dev_err(&chip->dev, "in retry loop\n");
			else
				dev_err(&chip->dev,
					"self test is still running\n");
			break;
		}
		tpm_msleep(delay_msec);
		delay_msec *= 2;
		memcpy(buf, save, save_size);
	}
	return ret;
}