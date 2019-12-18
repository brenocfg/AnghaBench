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
struct tpm_chip {int flags; } ;

/* Variables and functions */
 int TPM_CHIP_FLAG_HAVE_TIMEOUTS ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int tpm1_get_timeouts (struct tpm_chip*) ; 
 int tpm2_get_timeouts (struct tpm_chip*) ; 

int tpm_get_timeouts(struct tpm_chip *chip)
{
	if (chip->flags & TPM_CHIP_FLAG_HAVE_TIMEOUTS)
		return 0;

	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		return tpm2_get_timeouts(chip);
	else
		return tpm1_get_timeouts(chip);
}