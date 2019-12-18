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
struct tpm_softc {int sc_stat; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int PCATCH ; 
 int PRIBIO ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int tpm_status (struct tpm_softc*) ; 
 int tsleep (void*,int,char*,int) ; 

int
tpm_waitfor_poll(struct tpm_softc *sc, u_int8_t mask, int tmo, void *c)
{
	int rv;

	/*
	 * Poll until either the requested condition or a time out is
	 * met.
	 */
	while (((sc->sc_stat = tpm_status(sc)) & mask) != mask && tmo--) {
		rv = tsleep(c, PRIBIO | PCATCH, "tpm_poll", 1);
		if (rv && rv != EWOULDBLOCK) {
#ifdef TPM_DEBUG
			printf("tpm_waitfor_poll: interrupted %d\n", rv);
#endif
			return rv;
		}
	}

	return 0;
}