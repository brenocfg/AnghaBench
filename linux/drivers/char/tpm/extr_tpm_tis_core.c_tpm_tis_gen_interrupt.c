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
typedef  int /*<<< orphan*/  u32 ;
struct tpm_chip {int flags; } ;
typedef  int /*<<< orphan*/  cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_CAP_PROP_TIS_TIMEOUT ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 int tpm1_getcap (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int tpm2_get_tpm_pt (struct tpm_chip*,int,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int tpm_tis_gen_interrupt(struct tpm_chip *chip)
{
	const char *desc = "attempting to generate an interrupt";
	u32 cap2;
	cap_t cap;

	if (chip->flags & TPM_CHIP_FLAG_TPM2)
		return tpm2_get_tpm_pt(chip, 0x100, &cap2, desc);
	else
		return tpm1_getcap(chip, TPM_CAP_PROP_TIS_TIMEOUT, &cap, desc,
				  0);
}