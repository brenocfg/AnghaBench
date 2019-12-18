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
typedef  int /*<<< orphan*/  u_int8_t ;
struct tpm_softc {int sc_stat; int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  TPM_DATA ; 
 int /*<<< orphan*/  TPM_READ_TMO ; 
 int /*<<< orphan*/  TPM_STS_BITS ; 
 int TPM_STS_DATA_EXPECT ; 
 int /*<<< orphan*/  TPM_STS_VALID ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int tpm_getburst (struct tpm_softc*) ; 
 int tpm_request_locality (struct tpm_softc*,int /*<<< orphan*/ ) ; 
 int tpm_status (struct tpm_softc*) ; 
 int tpm_waitfor (struct tpm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tpm_softc*) ; 

int
tpm_tis12_write(struct tpm_softc *sc, void *buf, int len)
{
	u_int8_t *p = buf;
	size_t cnt;
	int rv, r;

#ifdef TPM_DEBUG
	printf("tpm_tis12_write: sc %p buf %p len %d\n", sc, buf, len);
#endif

	if ((rv = tpm_request_locality(sc, 0)) != 0)
		return rv;

	cnt = 0;
	while (cnt < len - 1) {
		for (r = tpm_getburst(sc); r > 0 && cnt < len - 1; r--) {
			bus_space_write_1(sc->sc_bt, sc->sc_bh, TPM_DATA, *p++);
			cnt++;
		}
		if ((rv = tpm_waitfor(sc, TPM_STS_VALID, TPM_READ_TMO, sc))) {
#ifdef TPM_DEBUG
			printf("tpm_tis12_write: failed burst rv %d\n", rv);
#endif
			return rv;
		}
		sc->sc_stat = tpm_status(sc);
		if (!(sc->sc_stat & TPM_STS_DATA_EXPECT)) {
#ifdef TPM_DEBUG
			printf("tpm_tis12_write: failed rv %d stat=%b\n", rv,
			    sc->sc_stat, TPM_STS_BITS);
#endif
			return EIO;
		}
	}

	bus_space_write_1(sc->sc_bt, sc->sc_bh, TPM_DATA, *p++);
	cnt++;

	if ((rv = tpm_waitfor(sc, TPM_STS_VALID, TPM_READ_TMO, sc))) {
#ifdef TPM_DEBUG
		printf("tpm_tis12_write: failed last byte rv %d\n", rv);
#endif
		return rv;
	}
	if ((sc->sc_stat & TPM_STS_DATA_EXPECT) != 0) {
#ifdef TPM_DEBUG
		printf("tpm_tis12_write: failed rv %d stat=%b\n", rv,
		    sc->sc_stat, TPM_STS_BITS);
#endif
		return EIO;
	}

#ifdef TPM_DEBUG
	printf("tpm_tis12_write: wrote %d byte\n", cnt);
#endif

	return 0;
}