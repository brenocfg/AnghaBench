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
struct aue_softc {int sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_REG_1D ; 
 int /*<<< orphan*/  AUE_REG_7B ; 
 int /*<<< orphan*/  AUE_REG_81 ; 
 int HAS_HOME_PNA ; 
 int /*<<< orphan*/  aue_csr_write_1 (struct aue_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mii_mode ; 

__attribute__((used)) static void
aue_reset_pegasus_II(struct aue_softc *sc)
{
	/* Magic constants taken from Linux driver. */
	aue_csr_write_1(sc, AUE_REG_1D, 0);
	aue_csr_write_1(sc, AUE_REG_7B, 2);
#if 0
	if ((sc->sc_flags & HAS_HOME_PNA) && mii_mode)
		aue_csr_write_1(sc, AUE_REG_81, 6);
	else
#endif
		aue_csr_write_1(sc, AUE_REG_81, 2);
}