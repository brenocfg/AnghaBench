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
typedef  int u_int32_t ;
struct tpm_softc {int /*<<< orphan*/  sc_init; int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EWOULDBLOCK ; 
 int PCATCH ; 
 int PRIBIO ; 
 int /*<<< orphan*/  TPM_ACCESS ; 
 int TPM_ACCESS_ACTIVE_LOCALITY ; 
 int /*<<< orphan*/  TPM_ACCESS_BITS ; 
 int /*<<< orphan*/  TPM_ACCESS_REQUEST_USE ; 
 int /*<<< orphan*/  TPM_ACCESS_TMO ; 
 int TPM_ACCESS_VALID ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int tpm_tmotohz (int /*<<< orphan*/ ) ; 
 int tsleep (int /*<<< orphan*/ ,int,char*,int) ; 

int
tpm_request_locality(struct tpm_softc *sc, int l)
{
	u_int32_t r;
	int to, rv;

	if (l != 0)
		return EINVAL;

	if ((bus_space_read_1(sc->sc_bt, sc->sc_bh, TPM_ACCESS) &
	    (TPM_ACCESS_VALID | TPM_ACCESS_ACTIVE_LOCALITY)) ==
	    (TPM_ACCESS_VALID | TPM_ACCESS_ACTIVE_LOCALITY))
		return 0;

	bus_space_write_1(sc->sc_bt, sc->sc_bh, TPM_ACCESS,
	    TPM_ACCESS_REQUEST_USE);

	to = tpm_tmotohz(TPM_ACCESS_TMO);

	while ((r = bus_space_read_1(sc->sc_bt, sc->sc_bh, TPM_ACCESS) &
	    (TPM_ACCESS_VALID | TPM_ACCESS_ACTIVE_LOCALITY)) !=
	    (TPM_ACCESS_VALID | TPM_ACCESS_ACTIVE_LOCALITY) && to--) {
		rv = tsleep(sc->sc_init, PRIBIO | PCATCH, "tpm_locality", 1);
		if (rv &&  rv != EWOULDBLOCK) {
#ifdef TPM_DEBUG
			printf("tpm_request_locality: interrupted %d\n", rv);
#endif
			return rv;
		}
	}

	if ((r & (TPM_ACCESS_VALID | TPM_ACCESS_ACTIVE_LOCALITY)) !=
	    (TPM_ACCESS_VALID | TPM_ACCESS_ACTIVE_LOCALITY)) {
#ifdef TPM_DEBUG
		printf("tpm_request_locality: access %b\n", r, TPM_ACCESS_BITS);
#endif
		return EBUSY;
	}

	return 0;
}