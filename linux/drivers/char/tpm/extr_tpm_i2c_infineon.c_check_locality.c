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
typedef  int u8 ;
struct tpm_chip {int dummy; } ;
struct TYPE_2__ {int locality; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_ACCESS (int) ; 
 int TPM_ACCESS_ACTIVE_LOCALITY ; 
 int TPM_ACCESS_VALID ; 
 int iic_tpm_read (int /*<<< orphan*/ ,int*,int) ; 
 TYPE_1__ tpm_dev ; 

__attribute__((used)) static bool check_locality(struct tpm_chip *chip, int loc)
{
	u8 buf;
	int rc;

	rc = iic_tpm_read(TPM_ACCESS(loc), &buf, 1);
	if (rc < 0)
		return false;

	if ((buf & (TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) ==
	    (TPM_ACCESS_ACTIVE_LOCALITY | TPM_ACCESS_VALID)) {
		tpm_dev.locality = loc;
		return true;
	}

	return false;
}