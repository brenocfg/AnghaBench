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
typedef  int /*<<< orphan*/  u8 ;
struct tpm_chip {unsigned long timeout_a; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  TPM_ACCESS (int) ; 
 int /*<<< orphan*/  TPM_ACCESS_REQUEST_USE ; 
 int /*<<< orphan*/  TPM_TIMEOUT_US_HI ; 
 int /*<<< orphan*/  TPM_TIMEOUT_US_LOW ; 
 scalar_t__ check_locality (struct tpm_chip*,int) ; 
 int /*<<< orphan*/  iic_tpm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_locality(struct tpm_chip *chip, int loc)
{
	unsigned long stop;
	u8 buf = TPM_ACCESS_REQUEST_USE;

	if (check_locality(chip, loc))
		return loc;

	iic_tpm_write(TPM_ACCESS(loc), &buf, 1);

	/* wait for burstcount */
	stop = jiffies + chip->timeout_a;
	do {
		if (check_locality(chip, loc))
			return loc;
		usleep_range(TPM_TIMEOUT_US_LOW, TPM_TIMEOUT_US_HI);
	} while (time_before(jiffies, stop));

	return -ETIME;
}