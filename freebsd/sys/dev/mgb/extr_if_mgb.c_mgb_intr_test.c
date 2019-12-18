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
struct mgb_softc {int isr_test_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  MGB_INTR_ENBL_CLR ; 
 int /*<<< orphan*/  MGB_INTR_ENBL_SET ; 
 int /*<<< orphan*/  MGB_INTR_SET ; 
 int /*<<< orphan*/  MGB_INTR_STS ; 
 int MGB_INTR_STS_ANY ; 
 int MGB_INTR_STS_TEST ; 
 int /*<<< orphan*/  MGB_INTR_VEC_ENBL_SET ; 
 int MGB_TIMEOUT ; 

__attribute__((used)) static bool
mgb_intr_test(struct mgb_softc *sc)
{
	int i;

	sc->isr_test_flag = false;
	CSR_WRITE_REG(sc, MGB_INTR_STS, MGB_INTR_STS_TEST);
	CSR_WRITE_REG(sc, MGB_INTR_VEC_ENBL_SET, MGB_INTR_STS_ANY);
	CSR_WRITE_REG(sc, MGB_INTR_ENBL_SET,
	    MGB_INTR_STS_ANY | MGB_INTR_STS_TEST);
	CSR_WRITE_REG(sc, MGB_INTR_SET, MGB_INTR_STS_TEST);
	if (sc->isr_test_flag)
		return true;
	for (i = 0; i < MGB_TIMEOUT; i++) {
		DELAY(10);
		if (sc->isr_test_flag)
			break;
	}
	CSR_WRITE_REG(sc, MGB_INTR_ENBL_CLR, MGB_INTR_STS_TEST);
	CSR_WRITE_REG(sc, MGB_INTR_STS, MGB_INTR_STS_TEST);
	return sc->isr_test_flag;
}