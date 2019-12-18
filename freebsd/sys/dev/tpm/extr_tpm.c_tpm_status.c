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
struct tpm_softc {int /*<<< orphan*/  sc_bh; int /*<<< orphan*/  sc_bt; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_STS ; 
 int TPM_STS_MASK ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u_int8_t
tpm_status(struct tpm_softc *sc)
{
	u_int8_t status;

	status = bus_space_read_1(sc->sc_bt, sc->sc_bh, TPM_STS) &
	    TPM_STS_MASK;

	return status;
}