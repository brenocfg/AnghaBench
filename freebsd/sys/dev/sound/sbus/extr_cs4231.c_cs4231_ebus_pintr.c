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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int u_int32_t ;
struct cs4231_channel {int togo; int nextaddr; int /*<<< orphan*/  channel; int /*<<< orphan*/  buffer; } ;
struct cs4231_softc {struct cs4231_channel sc_pch; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS_TEST_AND_INIT ; 
 int EBDCSR_ERR ; 
 int EBDCSR_INT ; 
 int EBDCSR_TC ; 
 int /*<<< orphan*/  EBDMA_DADDR ; 
 int /*<<< orphan*/  EBDMA_DCSR ; 
 int EBDMA_P_READ (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EBDMA_P_WRITE (struct cs4231_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  chn_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs4231_read (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cs4231_ebus_pintr(void *arg)
{
	struct cs4231_softc *sc;
	struct cs4231_channel *ch;
	u_int32_t csr;
	u_int8_t status;

	sc = arg;
	CS4231_LOCK(sc);

	csr = EBDMA_P_READ(sc, EBDMA_DCSR);
	if ((csr & EBDCSR_INT) == 0) {
		CS4231_UNLOCK(sc);
		return;
	}

	if ((csr & EBDCSR_ERR)) {
		status = cs4231_read(sc, CS_TEST_AND_INIT);
		device_printf(sc->sc_dev,
		    "ebdma error interrupt : stat = 0x%x\n", status);
	}
	EBDMA_P_WRITE(sc, EBDMA_DCSR, csr | EBDCSR_TC);

	ch = NULL;
	if (csr & EBDCSR_TC) {
		u_long nextaddr, saddr;
		u_int32_t togo;

		ch = &sc->sc_pch;
		togo = ch->togo;
		saddr = sndbuf_getbufaddr(ch->buffer);
		nextaddr = ch->nextaddr + togo;
		if (nextaddr >=  saddr + sndbuf_getsize(ch->buffer))
			nextaddr = saddr;
		/*
		 * EBDMA_DCNT is loaded automatically
		 * EBDMA_P_WRITE(sc, EBDMA_DCNT, togo);
		 */
		EBDMA_P_WRITE(sc, EBDMA_DADDR, nextaddr);
		ch->nextaddr = nextaddr;
	}
	CS4231_UNLOCK(sc);
	if (ch)
		chn_intr(ch->channel);
}