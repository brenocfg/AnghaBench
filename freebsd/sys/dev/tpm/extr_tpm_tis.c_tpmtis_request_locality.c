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
typedef  int uint8_t ;
struct tpm_sc {scalar_t__ interrupts; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  intr_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  PWAIT ; 
 int RD1 (struct tpm_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_ACCESS ; 
 int TPM_ACCESS_LOC_ACTIVE ; 
 int /*<<< orphan*/  TPM_ACCESS_LOC_REQ ; 
 int TPM_ACCESS_VALID ; 
 int /*<<< orphan*/  TPM_INT_STS_LOC_CHANGE ; 
 int TPM_TIMEOUT_A ; 
 int /*<<< orphan*/  WR1 (struct tpm_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int tick ; 
 int /*<<< orphan*/  tsleep (struct tpm_sc*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bool
tpmtis_request_locality(struct tpm_sc *sc, int locality)
{
	uint8_t mask;
	int timeout;

	/* Currently we only support Locality 0 */
	if (locality != 0)
		return (false);

	mask = TPM_ACCESS_LOC_ACTIVE | TPM_ACCESS_VALID;
	timeout = TPM_TIMEOUT_A;
	sc->intr_type = TPM_INT_STS_LOC_CHANGE;

	WR1(sc, TPM_ACCESS, TPM_ACCESS_LOC_REQ);
	bus_barrier(sc->mem_res, TPM_ACCESS, 1, BUS_SPACE_BARRIER_WRITE);
	if(sc->interrupts) {
		tsleep(sc, PWAIT, "TPMLOCREQUEST with INTR", timeout / tick);
		return ((RD1(sc, TPM_ACCESS) & mask) == mask);
	} else  {
		while(timeout > 0) {
			if ((RD1(sc, TPM_ACCESS) & mask) == mask)
				return (true);

			pause("TPMLOCREQUEST POLLING", 1);
			timeout -= tick;
		}
	}

	return (false);
}