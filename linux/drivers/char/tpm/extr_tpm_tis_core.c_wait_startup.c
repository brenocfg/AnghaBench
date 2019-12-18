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
typedef  int u8 ;
struct tpm_tis_data {int dummy; } ;
struct tpm_chip {unsigned long timeout_a; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_ACCESS (int) ; 
 int TPM_ACCESS_VALID ; 
 int /*<<< orphan*/  TPM_TIMEOUT ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  tpm_msleep (int /*<<< orphan*/ ) ; 
 int tpm_tis_read8 (struct tpm_tis_data*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int wait_startup(struct tpm_chip *chip, int l)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	unsigned long stop = jiffies + chip->timeout_a;

	do {
		int rc;
		u8 access;

		rc = tpm_tis_read8(priv, TPM_ACCESS(l), &access);
		if (rc < 0)
			return rc;

		if (access & TPM_ACCESS_VALID)
			return 0;
		tpm_msleep(TPM_TIMEOUT);
	} while (time_before(jiffies, stop));
	return -1;
}