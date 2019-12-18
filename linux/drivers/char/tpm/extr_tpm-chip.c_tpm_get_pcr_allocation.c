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
 int ENODEV ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int tpm1_get_pcr_allocation (struct tpm_chip*) ; 
 int tpm2_get_pcr_allocation (struct tpm_chip*) ; 

__attribute__((used)) static int tpm_get_pcr_allocation(struct tpm_chip *chip)
{
	int rc;

	rc = (chip->flags & TPM_CHIP_FLAG_TPM2) ?
	     tpm2_get_pcr_allocation(chip) :
	     tpm1_get_pcr_allocation(chip);

	if (rc > 0)
		return -ENODEV;

	return rc;
}