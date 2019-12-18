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
struct tpm_softc {int /*<<< orphan*/  sc_bahm; int /*<<< orphan*/  sc_batm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int /*<<< orphan*/ ) ; 
 int TPM_BUFSIZ ; 
 int /*<<< orphan*/  TPM_LEGACY_DELAY ; 
 int /*<<< orphan*/  TPM_LEGACY_LAST ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
tpm_legacy_write(struct tpm_softc *sc, void *buf, int len)
{
	u_int8_t *p;
	int n;

	for (p = buf, n = len; n--; DELAY(TPM_LEGACY_DELAY)) {
		if (!n && len != TPM_BUFSIZ) {
			bus_space_write_1(sc->sc_batm, sc->sc_bahm, 1,
			    TPM_LEGACY_LAST);
			DELAY(TPM_LEGACY_DELAY);
		}
		bus_space_write_1(sc->sc_batm, sc->sc_bahm, 0, *p++);
	}

	return 0;
}