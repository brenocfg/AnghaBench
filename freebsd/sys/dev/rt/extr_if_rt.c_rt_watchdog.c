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
struct rt_softc {scalar_t__ rt_chipid; int /*<<< orphan*/ * tx_queue_not_empty; } ;

/* Variables and functions */
 scalar_t__ CDMA_OQ_STA ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int P0_IQ_PCNT_SHIFT ; 
 int P1_IQ_PCNT_SHIFT ; 
 scalar_t__ PSE_BASE ; 
 scalar_t__ PSE_IQ_STA ; 
 scalar_t__ RT_CHIPID_MT7620 ; 
 scalar_t__ RT_CHIPID_MT7621 ; 
 scalar_t__ RT_CHIPID_RT5350 ; 
 int /*<<< orphan*/  RT_DEBUG_WATCHDOG ; 
 int /*<<< orphan*/  RT_DPRINTF (struct rt_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int RT_READ (struct rt_softc*,scalar_t__) ; 

__attribute__((used)) static void
rt_watchdog(struct rt_softc *sc)
{
	uint32_t tmp;
#ifdef notyet
	int ntries;
#endif
	if(sc->rt_chipid != RT_CHIPID_RT5350 &&
	   sc->rt_chipid != RT_CHIPID_MT7620 &&
	   sc->rt_chipid != RT_CHIPID_MT7621) {
		tmp = RT_READ(sc, PSE_BASE + CDMA_OQ_STA);

		RT_DPRINTF(sc, RT_DEBUG_WATCHDOG,
			   "watchdog: PSE_IQ_STA=0x%08x\n", tmp);
	}
	/* XXX: do not reset */
#ifdef notyet
	if (((tmp >> P0_IQ_PCNT_SHIFT) & 0xff) != 0) {
		sc->tx_queue_not_empty[0]++;

		for (ntries = 0; ntries < 10; ntries++) {
			tmp = RT_READ(sc, PSE_BASE + PSE_IQ_STA);
			if (((tmp >> P0_IQ_PCNT_SHIFT) & 0xff) == 0)
				break;

			DELAY(1);
		}
	}

	if (((tmp >> P1_IQ_PCNT_SHIFT) & 0xff) != 0) {
		sc->tx_queue_not_empty[1]++;

		for (ntries = 0; ntries < 10; ntries++) {
			tmp = RT_READ(sc, PSE_BASE + PSE_IQ_STA);
			if (((tmp >> P1_IQ_PCNT_SHIFT) & 0xff) == 0)
				break;

			DELAY(1);
		}
	}
#endif
}