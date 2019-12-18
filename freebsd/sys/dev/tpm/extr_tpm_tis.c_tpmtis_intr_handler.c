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
typedef  int uint32_t ;
struct tpm_sc {int intr_type; } ;

/* Variables and functions */
 int RD4 (struct tpm_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_INT_STS ; 
 int /*<<< orphan*/  WR4 (struct tpm_sc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wakeup (struct tpm_sc*) ; 

__attribute__((used)) static void
tpmtis_intr_handler(void *arg)
{
	struct tpm_sc *sc;
	uint32_t status;

	sc = (struct tpm_sc *)arg;
	status = RD4(sc, TPM_INT_STS);

	WR4(sc, TPM_INT_STS, status);
	if (sc->intr_type != -1 && sc->intr_type & status)
		wakeup(sc);
}