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

/* Variables and functions */
 int /*<<< orphan*/  TPM_ADDR ; 
 int tpm_read_index (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int atmel_verify_tpm11(void)
{

	/* verify that it is an Atmel part */
	if (tpm_read_index(TPM_ADDR, 4) != 'A' ||
	    tpm_read_index(TPM_ADDR, 5) != 'T' ||
	    tpm_read_index(TPM_ADDR, 6) != 'M' ||
	    tpm_read_index(TPM_ADDR, 7) != 'L')
		return 1;

	/* query chip for its version number */
	if (tpm_read_index(TPM_ADDR, 0x00) != 1 ||
	    tpm_read_index(TPM_ADDR, 0x01) != 1)
		return 1;

	/* This is an atmel supported part */
	return 0;
}