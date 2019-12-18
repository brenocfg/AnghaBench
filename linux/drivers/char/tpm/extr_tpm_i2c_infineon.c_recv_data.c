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
typedef  scalar_t__ u8 ;
struct tpm_chip {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  locality; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ MAX_COUNT_LONG ; 
 int /*<<< orphan*/  TPM_DATA_FIFO (int /*<<< orphan*/ ) ; 
 int get_burstcount (struct tpm_chip*) ; 
 int iic_tpm_read (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 TYPE_1__ tpm_dev ; 

__attribute__((used)) static int recv_data(struct tpm_chip *chip, u8 *buf, size_t count)
{
	size_t size = 0;
	ssize_t burstcnt;
	u8 retries = 0;
	int rc;

	while (size < count) {
		burstcnt = get_burstcount(chip);

		/* burstcnt < 0 = TPM is busy */
		if (burstcnt < 0)
			return burstcnt;

		/* limit received data to max. left */
		if (burstcnt > (count - size))
			burstcnt = count - size;

		rc = iic_tpm_read(TPM_DATA_FIFO(tpm_dev.locality),
				  &(buf[size]), burstcnt);
		if (rc == 0)
			size += burstcnt;
		else if (rc < 0)
			retries++;

		/* avoid endless loop in case of broken HW */
		if (retries > MAX_COUNT_LONG)
			return -EIO;
	}
	return size;
}