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
struct tpm_sc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OR4 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_LOC_CTRL ; 
 int /*<<< orphan*/  TPM_LOC_CTRL_RELINQUISH ; 

__attribute__((used)) static void
tpmcrb_relinquish_locality(struct tpm_sc *sc)
{

	OR4(sc, TPM_LOC_CTRL, TPM_LOC_CTRL_RELINQUISH);
}