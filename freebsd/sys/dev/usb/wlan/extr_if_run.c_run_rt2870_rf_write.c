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
typedef  int uint32_t ;
struct run_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RT2860_RF_CSR_CFG0 ; 
 int RT2860_RF_REG_CTRL ; 
 int run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 
 int run_write (struct run_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
run_rt2870_rf_write(struct run_softc *sc, uint32_t val)
{
	uint32_t tmp;
	int error, ntries;

	for (ntries = 0; ntries < 10; ntries++) {
		if ((error = run_read(sc, RT2860_RF_CSR_CFG0, &tmp)) != 0)
			return (error);
		if (!(tmp & RT2860_RF_REG_CTRL))
			break;
	}
	if (ntries == 10)
		return (ETIMEDOUT);

	return (run_write(sc, RT2860_RF_CSR_CFG0, val));
}