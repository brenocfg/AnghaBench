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
struct tpm_sc {scalar_t__ interrupts; } ;

/* Variables and functions */
 int /*<<< orphan*/  AND4 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OR1 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RD4 (struct tpm_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_ACCESS ; 
 int /*<<< orphan*/  TPM_ACCESS_LOC_RELINQUISH ; 
 int /*<<< orphan*/  TPM_INT_STS ; 

__attribute__((used)) static void
tpmtis_relinquish_locality(struct tpm_sc *sc)
{

	/*
	 * Interrupts can only be cleared when a locality is active.
	 * Clear them now in case interrupt handler didn't make it in time.
	 */
	if(sc->interrupts)
		AND4(sc, TPM_INT_STS, RD4(sc, TPM_INT_STS));

	OR1(sc, TPM_ACCESS, TPM_ACCESS_LOC_RELINQUISH);
}