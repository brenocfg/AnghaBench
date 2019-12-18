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
struct tpm_sc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OR4 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_LOC_CTRL ; 
 int /*<<< orphan*/  TPM_LOC_CTRL_REQUEST ; 
 int /*<<< orphan*/  TPM_LOC_STATE ; 
 int TPM_LOC_STATE_ASSIGNED ; 
 int TPM_LOC_STATE_VALID ; 
 int /*<<< orphan*/  TPM_TIMEOUT_C ; 
 int /*<<< orphan*/  tpm_wait_for_u32 (struct tpm_sc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tpmcrb_request_locality(struct tpm_sc *sc, int locality)
{
	uint32_t mask;

	/* Currently we only support Locality 0 */
	if (locality != 0)
		return (false);

	mask = TPM_LOC_STATE_VALID | TPM_LOC_STATE_ASSIGNED;

	OR4(sc, TPM_LOC_CTRL, TPM_LOC_CTRL_REQUEST);
	if (!tpm_wait_for_u32(sc, TPM_LOC_STATE, mask, mask, TPM_TIMEOUT_C))
		return (false);

	return (true);
}