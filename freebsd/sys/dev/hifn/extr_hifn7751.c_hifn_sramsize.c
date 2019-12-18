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
typedef  int u_int32_t ;
struct hifn_softc {int sc_ramsize; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  i ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int HIFN_SRAM_GRANULARITY ; 
 int HIFN_SRAM_STEP_SIZE ; 
 scalar_t__ bcmp (int*,int*,int) ; 
 int /*<<< orphan*/  bcopy (int*,int*,int) ; 
 scalar_t__ hifn_readramaddr (struct hifn_softc*,int,int*) ; 
 int /*<<< orphan*/  hifn_writeramaddr (struct hifn_softc*,int,int*) ; 

__attribute__((used)) static int
hifn_sramsize(struct hifn_softc *sc)
{
	u_int32_t a;
	u_int8_t data[8];
	u_int8_t dataexpect[sizeof(data)];
	int32_t i;

	for (i = 0; i < sizeof(data); i++)
		data[i] = dataexpect[i] = i ^ 0x5a;

	for (i = HIFN_SRAM_GRANULARITY - 1; i >= 0; i--) {
		a = i * HIFN_SRAM_STEP_SIZE;
		bcopy(&i, data, sizeof(i));
		hifn_writeramaddr(sc, a, data);
	}

	for (i = 0; i < HIFN_SRAM_GRANULARITY; i++) {
		a = i * HIFN_SRAM_STEP_SIZE;
		bcopy(&i, dataexpect, sizeof(i));
		if (hifn_readramaddr(sc, a, data) < 0)
			return (0);
		if (bcmp(data, dataexpect, sizeof(data)) != 0)
			return (0);
		sc->sc_ramsize = a + HIFN_SRAM_STEP_SIZE;
	}

	return (0);
}