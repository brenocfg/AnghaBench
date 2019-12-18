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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct rt2661_softc {int dummy; } ;

/* Variables and functions */
 int RAL_READ (struct rt2661_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2661_DISABLE_RX ; 
 int /*<<< orphan*/  RT2661_TXRX_CSR0 ; 
 int /*<<< orphan*/  rt2661_bbp_read (struct rt2661_softc*,int) ; 
 int /*<<< orphan*/  rt2661_bbp_write (struct rt2661_softc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2661_select_antenna(struct rt2661_softc *sc)
{
	uint8_t bbp4, bbp77;
	uint32_t tmp;

	bbp4  = rt2661_bbp_read(sc,  4);
	bbp77 = rt2661_bbp_read(sc, 77);

	/* TBD */

	/* make sure Rx is disabled before switching antenna */
	tmp = RAL_READ(sc, RT2661_TXRX_CSR0);
	RAL_WRITE(sc, RT2661_TXRX_CSR0, tmp | RT2661_DISABLE_RX);

	rt2661_bbp_write(sc,  4, bbp4);
	rt2661_bbp_write(sc, 77, bbp77);

	/* restore Rx filter */
	RAL_WRITE(sc, RT2661_TXRX_CSR0, tmp);
}