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
struct tpm_chip {int /*<<< orphan*/  flags; void** duration; void* timeout_d; void* timeout_c; void* timeout_b; void* timeout_a; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM2_DURATION_LONG ; 
 int /*<<< orphan*/  TPM2_DURATION_LONG_LONG ; 
 int /*<<< orphan*/  TPM2_DURATION_MEDIUM ; 
 int /*<<< orphan*/  TPM2_DURATION_SHORT ; 
 int /*<<< orphan*/  TPM2_TIMEOUT_A ; 
 int /*<<< orphan*/  TPM2_TIMEOUT_B ; 
 int /*<<< orphan*/  TPM2_TIMEOUT_C ; 
 int /*<<< orphan*/  TPM2_TIMEOUT_D ; 
 int /*<<< orphan*/  TPM_CHIP_FLAG_HAVE_TIMEOUTS ; 
 size_t TPM_LONG ; 
 size_t TPM_LONG_LONG ; 
 size_t TPM_MEDIUM ; 
 size_t TPM_SHORT ; 
 void* msecs_to_jiffies (int /*<<< orphan*/ ) ; 

int tpm2_get_timeouts(struct tpm_chip *chip)
{
	/* Fixed timeouts for TPM2 */
	chip->timeout_a = msecs_to_jiffies(TPM2_TIMEOUT_A);
	chip->timeout_b = msecs_to_jiffies(TPM2_TIMEOUT_B);
	chip->timeout_c = msecs_to_jiffies(TPM2_TIMEOUT_C);
	chip->timeout_d = msecs_to_jiffies(TPM2_TIMEOUT_D);

	/* PTP spec timeouts */
	chip->duration[TPM_SHORT] = msecs_to_jiffies(TPM2_DURATION_SHORT);
	chip->duration[TPM_MEDIUM] = msecs_to_jiffies(TPM2_DURATION_MEDIUM);
	chip->duration[TPM_LONG] = msecs_to_jiffies(TPM2_DURATION_LONG);

	/* Key creation commands long timeouts */
	chip->duration[TPM_LONG_LONG] =
		msecs_to_jiffies(TPM2_DURATION_LONG_LONG);

	chip->flags |= TPM_CHIP_FLAG_HAVE_TIMEOUTS;

	return 0;
}