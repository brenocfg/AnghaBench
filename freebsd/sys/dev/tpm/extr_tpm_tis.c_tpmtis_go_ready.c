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
typedef  int /*<<< orphan*/  uint32_t ;
struct tpm_sc {int /*<<< orphan*/  mem_res; int /*<<< orphan*/  intr_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AND4 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  OR4 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_INT_STS_CMD_RDY ; 
 int /*<<< orphan*/  TPM_STS ; 
 int /*<<< orphan*/  TPM_STS_CMD_RDY ; 
 int /*<<< orphan*/  TPM_TIMEOUT_B ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_wait_for_u32 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tpmtis_go_ready(struct tpm_sc *sc)
{
	uint32_t mask;

	mask = TPM_STS_CMD_RDY;
	sc->intr_type = TPM_INT_STS_CMD_RDY;

	OR4(sc, TPM_STS, TPM_STS_CMD_RDY);
	bus_barrier(sc->mem_res, TPM_STS, 4, BUS_SPACE_BARRIER_WRITE);
	if (!tpm_wait_for_u32(sc, TPM_STS, mask, mask, TPM_TIMEOUT_B))
		return (false);

	AND4(sc, TPM_STS, ~TPM_STS_CMD_RDY);
	return (true);
}