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
typedef  int u_long ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  csa_res ;

/* Variables and functions */
 int ACCTL_DCV ; 
 int ACCTL_ESYN ; 
 int ACCTL_RSTN ; 
 int ACCTL_VFRM ; 
 int BA0_AC97_RESET ; 
 int /*<<< orphan*/  BA0_ACCAD ; 
 int /*<<< orphan*/  BA0_ACCDA ; 
 int /*<<< orphan*/  BA0_ACCTL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EAGAIN ; 
 int csa_readio (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csa_writeio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
csa_writecodec(csa_res *resp, u_long offset, u_int32_t data)
{
	int i;
	u_int32_t acctl;

	/*
	 * Setup the AC97 control registers on the CS461x to send the
	 * appropriate command to the AC97 to perform the write.
	 * ACCAD = Command Address Register = 46Ch
	 * ACCDA = Command Data Register = 470h
	 * ACCTL = Control Register = 460h
	 * set DCV - will clear when process completed
	 * set VFRM - valid frame enabled
	 * set ESYN - ASYNC generation enabled
	 * set RSTN - ARST# inactive, AC97 codec not reset
	 */

	/*
	 * Get the actual AC97 register from the offset
	 */
	csa_writeio(resp, BA0_ACCAD, offset - BA0_AC97_RESET);
	csa_writeio(resp, BA0_ACCDA, data);
	csa_writeio(resp, BA0_ACCTL, ACCTL_DCV | ACCTL_VFRM | ACCTL_ESYN | ACCTL_RSTN);

	/*
	 * Wait for the write to occur.
	 */
	acctl = 0;
	for (i = 0 ; i < 10 ; i++) {
		/*
		 * First, we want to wait for a short time.
		 */
		DELAY(25);

		/*
		 * Now, check to see if the read has completed.
		 * ACCTL = 460h, DCV should be reset by now and 460h = 17h
		 */
		acctl = csa_readio(resp, BA0_ACCTL);
		if ((acctl & ACCTL_DCV) == 0)
			break;
	}

	/*
	 * Make sure the write completed.
	 */
	if ((acctl & ACCTL_DCV) != 0)
		return (EAGAIN);

	return (0);
}