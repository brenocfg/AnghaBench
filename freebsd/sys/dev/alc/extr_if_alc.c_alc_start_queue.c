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
struct alc_softc {int alc_flags; } ;

/* Variables and functions */
 int ALC_FLAG_AR816X_FAMILY ; 
 int /*<<< orphan*/  ALC_LOCK_ASSERT (struct alc_softc*) ; 
 int /*<<< orphan*/  ALC_RXQ_CFG ; 
 int /*<<< orphan*/  ALC_TXQ_CFG ; 
 int CSR_READ_4 (struct alc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct alc_softc*,int /*<<< orphan*/ ,int) ; 
 int RXQ_CFG_ENB ; 
 int RXQ_CFG_QUEUE0_ENB ; 
 int RXQ_CFG_QUEUE1_ENB ; 
 int RXQ_CFG_QUEUE2_ENB ; 
 int TXQ_CFG_ENB ; 

__attribute__((used)) static void
alc_start_queue(struct alc_softc *sc)
{
	uint32_t qcfg[] = {
		0,
		RXQ_CFG_QUEUE0_ENB,
		RXQ_CFG_QUEUE0_ENB | RXQ_CFG_QUEUE1_ENB,
		RXQ_CFG_QUEUE0_ENB | RXQ_CFG_QUEUE1_ENB | RXQ_CFG_QUEUE2_ENB,
		RXQ_CFG_ENB
	};
	uint32_t cfg;

	ALC_LOCK_ASSERT(sc);

	/* Enable RxQ. */
	cfg = CSR_READ_4(sc, ALC_RXQ_CFG);
	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) == 0) {
		cfg &= ~RXQ_CFG_ENB;
		cfg |= qcfg[1];
	} else
		cfg |= RXQ_CFG_QUEUE0_ENB;
	CSR_WRITE_4(sc, ALC_RXQ_CFG, cfg);
	/* Enable TxQ. */
	cfg = CSR_READ_4(sc, ALC_TXQ_CFG);
	cfg |= TXQ_CFG_ENB;
	CSR_WRITE_4(sc, ALC_TXQ_CFG, cfg);
}