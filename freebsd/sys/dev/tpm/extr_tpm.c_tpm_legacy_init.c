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
struct tpm_softc {int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; int /*<<< orphan*/  sc_bahm; int /*<<< orphan*/  sc_batm; } ;
typedef  int /*<<< orphan*/  id ;

/* Variables and functions */
 scalar_t__ TPM_ID ; 
 int bus_space_map (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int tpm_enabled ; 
 char tpm_legacy_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int
tpm_legacy_init(struct tpm_softc *sc, int irq, const char *name)
{
	char id[8];
	u_int8_t ioh, iol;
	int i;

	if ((i = bus_space_map(sc->sc_batm, tpm_enabled, 2, 0, &sc->sc_bahm))) {
		printf(": cannot map tpm registers (%d)\n", i);
		tpm_enabled = 0;
		return 1;
	}

	for (i = sizeof(id); i--; )
		id[i] = tpm_legacy_in(sc->sc_bt, sc->sc_bh, TPM_ID + i);

	printf(": %.4s %d.%d @0x%x\n", &id[4], id[0], id[1], tpm_enabled);
	iol = tpm_enabled & 0xff;
	ioh = tpm_enabled >> 16;
	tpm_enabled = 0;

	return 0;
}