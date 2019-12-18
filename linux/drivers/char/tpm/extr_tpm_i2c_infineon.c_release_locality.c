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
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_ACCESS (int) ; 
 int TPM_ACCESS_ACTIVE_LOCALITY ; 
 int TPM_ACCESS_REQUEST_PENDING ; 
 int TPM_ACCESS_VALID ; 
 scalar_t__ iic_tpm_read (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  iic_tpm_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void release_locality(struct tpm_chip *chip, int loc, int force)
{
	u8 buf;
	if (iic_tpm_read(TPM_ACCESS(loc), &buf, 1) < 0)
		return;

	if (force || (buf & (TPM_ACCESS_REQUEST_PENDING | TPM_ACCESS_VALID)) ==
	    (TPM_ACCESS_REQUEST_PENDING | TPM_ACCESS_VALID)) {
		buf = TPM_ACCESS_ACTIVE_LOCALITY;
		iic_tpm_write(TPM_ACCESS(loc), &buf, 1);
	}
}