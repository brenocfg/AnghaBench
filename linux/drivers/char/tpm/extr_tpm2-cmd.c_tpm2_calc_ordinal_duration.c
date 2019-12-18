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
struct tpm_chip {unsigned long* duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM2_DURATION_DEFAULT ; 
 unsigned int TPM_UNDEFINED ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 unsigned int tpm2_ordinal_duration_index (int /*<<< orphan*/ ) ; 

unsigned long tpm2_calc_ordinal_duration(struct tpm_chip *chip, u32 ordinal)
{
	unsigned int index;

	index = tpm2_ordinal_duration_index(ordinal);

	if (index != TPM_UNDEFINED)
		return chip->duration[index];
	else
		return msecs_to_jiffies(TPM2_DURATION_DEFAULT);
}