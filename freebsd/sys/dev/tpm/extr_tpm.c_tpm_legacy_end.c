#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct TYPE_2__ {char* dv_xname; } ;
struct tpm_softc {TYPE_1__ sc_dev; int /*<<< orphan*/  sc_bahm; int /*<<< orphan*/  sc_batm; } ;
struct timeval {scalar_t__ tv_usec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int EIO ; 
 int EWOULDBLOCK ; 
 int PCATCH ; 
 int PRIBIO ; 
 int /*<<< orphan*/  TPM_LEGACY_ABRT ; 
 int /*<<< orphan*/  TPM_LEGACY_BITS ; 
 int TPM_LEGACY_BUSY ; 
 int TPM_LEGACY_RE ; 
 int TPM_LEGACY_SLEEP ; 
 int /*<<< orphan*/  TPM_LEGACY_TMO ; 
 int UIO_READ ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int /*<<< orphan*/ ) ; 
 int tsleep (struct tpm_softc*,int,char*,int) ; 
 int tvtohz (struct timeval*) ; 

int
tpm_legacy_end(struct tpm_softc *sc, int flag, int rv)
{
	struct timeval tv;
	u_int8_t r;
	int to;

	if (rv || flag == UIO_READ)
		bus_space_write_1(sc->sc_batm, sc->sc_bahm, 1, TPM_LEGACY_ABRT);
	else {
		tv.tv_sec = TPM_LEGACY_TMO;
		tv.tv_usec = 0;
		to = tvtohz(&tv) / TPM_LEGACY_SLEEP;
		while(((r = bus_space_read_1(sc->sc_batm, sc->sc_bahm, 1)) &
		    TPM_LEGACY_BUSY) && to--) {
			rv = tsleep(sc, PRIBIO | PCATCH, "legacy_tpm_end",
			    TPM_LEGACY_SLEEP);
			if (rv && rv != EWOULDBLOCK)
				return rv;
		}

#if defined(TPM_DEBUG) && !defined(__FreeBSD__)
		printf("%s: bits %b\n", sc->sc_dev.dv_xname, r, TPM_LEGACY_BITS);
#endif
		if (r & TPM_LEGACY_BUSY)
			return EIO;

		if (r & TPM_LEGACY_RE)
			return EIO;	/* XXX Retry the loop? */
	}

	return rv;
}