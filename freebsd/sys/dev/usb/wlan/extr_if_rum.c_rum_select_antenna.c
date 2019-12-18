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
struct rum_softc {int dummy; } ;

/* Variables and functions */
 int RT2573_DISABLE_RX ; 
 int /*<<< orphan*/  RT2573_TXRX_CSR0 ; 
 int /*<<< orphan*/  rum_bbp_read (struct rum_softc*,int) ; 
 int /*<<< orphan*/  rum_bbp_write (struct rum_softc*,int,int /*<<< orphan*/ ) ; 
 int rum_read (struct rum_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_write (struct rum_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rum_select_antenna(struct rum_softc *sc)
{
	uint8_t bbp4, bbp77;
	uint32_t tmp;

	bbp4  = rum_bbp_read(sc, 4);
	bbp77 = rum_bbp_read(sc, 77);

	/* TBD */

	/* make sure Rx is disabled before switching antenna */
	tmp = rum_read(sc, RT2573_TXRX_CSR0);
	rum_write(sc, RT2573_TXRX_CSR0, tmp | RT2573_DISABLE_RX);

	rum_bbp_write(sc,  4, bbp4);
	rum_bbp_write(sc, 77, bbp77);

	rum_write(sc, RT2573_TXRX_CSR0, tmp);
}