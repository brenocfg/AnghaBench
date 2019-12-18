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
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  STAT ; 
 int STAT_RDA ; 
 int STAT_XFE ; 
 int TPM_MAX_TRIES ; 
 int /*<<< orphan*/  TPM_MSLEEP_TIME ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int tpm_data_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_msleep (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait(struct tpm_chip *chip, int wait_for_bit)
{
	int status;
	int i;
	for (i = 0; i < TPM_MAX_TRIES; i++) {
		status = tpm_data_in(STAT);
		/* check the status-register if wait_for_bit is set */
		if (status & 1 << wait_for_bit)
			break;
		tpm_msleep(TPM_MSLEEP_TIME);
	}
	if (i == TPM_MAX_TRIES) {	/* timeout occurs */
		if (wait_for_bit == STAT_XFE)
			dev_err(&chip->dev, "Timeout in wait(STAT_XFE)\n");
		if (wait_for_bit == STAT_RDA)
			dev_err(&chip->dev, "Timeout in wait(STAT_RDA)\n");
		return -EIO;
	}
	return 0;
}