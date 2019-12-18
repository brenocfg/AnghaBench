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
struct tpm_chip {int flags; TYPE_1__* ops; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int TPM_CHIP_FLAG_TPM2 ; 
 int TPM_OPS_AUTO_STARTUP ; 
 int tpm1_auto_startup (struct tpm_chip*) ; 
 int tpm2_auto_startup (struct tpm_chip*) ; 

int tpm_auto_startup(struct tpm_chip *chip)
{
	int rc;

	if (!(chip->ops->flags & TPM_OPS_AUTO_STARTUP))
		return 0;

	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		rc = tpm2_auto_startup(chip);
	else
		rc = tpm1_auto_startup(chip);

	return rc;
}