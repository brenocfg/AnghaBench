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
typedef  int u_int8_t ;
struct tpm_softc {scalar_t__ sc_vector; int sc_capabilities; int sc_stat; int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IRQUNK ; 
 int /*<<< orphan*/  TPM_DATA_AVAIL_INT ; 
 int TPM_INTF_DATA_AVAIL_INT ; 
 int TPM_INTF_STS_VALID_INT ; 
 int /*<<< orphan*/  TPM_STS ; 
 int /*<<< orphan*/  TPM_STS_BITS ; 
 int TPM_STS_DATA_AVAIL ; 
 int /*<<< orphan*/  TPM_STS_RESP_RETRY ; 
 int TPM_STS_VALID ; 
 int /*<<< orphan*/  TPM_STS_VALID_INT ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,...) ; 
 int tpm_tmotohz (int) ; 
 int tpm_waitfor_int (struct tpm_softc*,int,int,void*,int /*<<< orphan*/ ) ; 
 int tpm_waitfor_poll (struct tpm_softc*,int,int,void*) ; 

int
tpm_waitfor(struct tpm_softc *sc, u_int8_t b0, int tmo, void *c)
{
	u_int8_t b;
	int re, to, rv;

#ifdef TPM_DEBUG
	printf("tpm_waitfor: b0 %b\n", b0, TPM_STS_BITS);
#endif

	/*
	 * If possible, use interrupts, otherwise poll.
	 *
	 * We use interrupts for TPM_STS_VALID and TPM_STS_DATA_AVAIL (if
	 * the tpm chips supports them) as waiting for those can take
	 * really long.  The other TPM_STS* are not needed very often
	 * so we do not support them.
	 */
	if (sc->sc_vector != IRQUNK) {
		b = b0;

		/*
		 * Wait for data ready.  This interrupt only occurs
		 * when both TPM_STS_VALID and TPM_STS_DATA_AVAIL are asserted.
		 * Thus we don't have to bother with TPM_STS_VALID
		 * separately and can just return.
		 *
		 * This only holds for interrupts!  When using polling
		 * both flags have to be waited for, see below.
		 */
		if ((b & TPM_STS_DATA_AVAIL) && (sc->sc_capabilities &
		    TPM_INTF_DATA_AVAIL_INT))
			return tpm_waitfor_int(sc, b, tmo, c,
			    TPM_DATA_AVAIL_INT);

		/* Wait for status valid bit. */
		if ((b & TPM_STS_VALID) && (sc->sc_capabilities &
		    TPM_INTF_STS_VALID_INT)) {
			rv = tpm_waitfor_int(sc, b, tmo, c, TPM_STS_VALID_INT);
			if (rv != 0)
				return rv;
			else
				b = b0 & ~TPM_STS_VALID;
		}

		/*
		 * When all flags are taken care of, return.  Otherwise
		 * use polling for eg. TPM_STS_CMD_READY.
		 */
		if (b == 0)
			return 0;
	}

	re = 3;
restart:
	/*
	 * If requested wait for TPM_STS_VALID before dealing with
	 * any other flag.  Eg. when both TPM_STS_DATA_AVAIL and TPM_STS_VALID
	 * are requested, wait for the latter first.
	 */
	b = b0;
	if (b0 & TPM_STS_VALID)
		b = TPM_STS_VALID;

	to = tpm_tmotohz(tmo);
again:
	if ((rv = tpm_waitfor_poll(sc, b, to, c)) != 0)
		return rv;

	if ((b & sc->sc_stat) == TPM_STS_VALID) {
		/* Now wait for other flags. */
		b = b0 & ~TPM_STS_VALID;
		to++;
		goto again;
	}

	if ((sc->sc_stat & b) != b) {
#ifdef TPM_DEBUG
		printf("tpm_waitfor: timeout: stat=%b b=%b\n",
		    sc->sc_stat, TPM_STS_BITS, b, TPM_STS_BITS);
#endif
		if (re-- && (b0 & TPM_STS_VALID)) {
			bus_space_write_1(sc->sc_bt, sc->sc_bh, TPM_STS,
			    TPM_STS_RESP_RETRY);
			goto restart;
		}
		return EIO;
	}

	return 0;
}