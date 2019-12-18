#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int (* mtkswitch_read ) (struct mtkswitch_softc*,int /*<<< orphan*/ ) ;} ;
struct mtkswitch_softc {TYPE_1__ hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MTKSWITCH_DUPLEX ; 
 int MTKSWITCH_LINK_UP ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_PMSR (int) ; 
 int MTKSWITCH_RXFLOW ; 
 int MTKSWITCH_SPEED_10 ; 
 int MTKSWITCH_SPEED_100 ; 
 int MTKSWITCH_SPEED_1000 ; 
 int MTKSWITCH_TXFLOW ; 
 int PMSR_MAC_DPX_STS ; 
 int PMSR_MAC_LINK_STS ; 
 int PMSR_MAC_SPD (int) ; 
 int PMSR_RX_FC_STS ; 
 int PMSR_TX_FC_STS ; 
 int stub1 (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
mtkswitch_get_port_status(struct mtkswitch_softc *sc, int port)
{
	uint32_t val, res, tmp;

	MTKSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	res = 0;
	val = sc->hal.mtkswitch_read(sc, MTKSWITCH_PMSR(port));

	if (val & PMSR_MAC_LINK_STS)
		res |= MTKSWITCH_LINK_UP;
	if (val & PMSR_MAC_DPX_STS)
		res |= MTKSWITCH_DUPLEX;
	tmp = PMSR_MAC_SPD(val);
	if (tmp == 0)
		res |= MTKSWITCH_SPEED_10;
	else if (tmp == 1)
		res |= MTKSWITCH_SPEED_100;
	else if (tmp == 2)
		res |= MTKSWITCH_SPEED_1000;
	if (val & PMSR_TX_FC_STS)
		res |= MTKSWITCH_TXFLOW;
	if (val & PMSR_RX_FC_STS)
		res |= MTKSWITCH_RXFLOW;

	return (res);
}