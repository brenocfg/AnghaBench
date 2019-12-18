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
struct mtkswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MTKSWITCH_DUPLEX ; 
 int MTKSWITCH_LINK_UP ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_POA ; 
 scalar_t__ MTKSWITCH_PORT_IS_100M (int) ; 
 int MTKSWITCH_READ (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int MTKSWITCH_RXFLOW ; 
 int MTKSWITCH_SPEED_10 ; 
 int MTKSWITCH_SPEED_100 ; 
 int MTKSWITCH_SPEED_1000 ; 
 int MTKSWITCH_TXFLOW ; 
 int POA_FE_SPEED (int) ; 
 int POA_FE_XFC (int) ; 
 int POA_GE_SPEED (int,int) ; 
#define  POA_GE_SPEED_10 130 
#define  POA_GE_SPEED_100 129 
#define  POA_GE_SPEED_1000 128 
 int POA_GE_XFC (int,int) ; 
 int POA_GE_XFC_RX_MSK ; 
 int POA_GE_XFC_TX_MSK ; 
 int POA_PRT_DPX (int) ; 
 int POA_PRT_LINK (int) ; 

__attribute__((used)) static uint32_t
mtkswitch_get_port_status(struct mtkswitch_softc *sc, int port)
{
	uint32_t val, res;

	MTKSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	res = 0;
	val = MTKSWITCH_READ(sc, MTKSWITCH_POA);

	if (val & POA_PRT_LINK(port))
		res |= MTKSWITCH_LINK_UP;
	if (val & POA_PRT_DPX(port))
		res |= MTKSWITCH_DUPLEX;

	if (MTKSWITCH_PORT_IS_100M(port)) {
		if (val & POA_FE_SPEED(port))
			res |= MTKSWITCH_SPEED_100;
		if (val & POA_FE_XFC(port))
			res |= (MTKSWITCH_TXFLOW | MTKSWITCH_RXFLOW);
	} else {
		switch (POA_GE_SPEED(val, port)) {
		case POA_GE_SPEED_10:
			res |= MTKSWITCH_SPEED_10;
			break;
		case POA_GE_SPEED_100:
			res |= MTKSWITCH_SPEED_100;
			break;
		case POA_GE_SPEED_1000:
			res |= MTKSWITCH_SPEED_1000;
			break;
		}

		val = POA_GE_XFC(val, port);
		if (val & POA_GE_XFC_TX_MSK)
			res |= MTKSWITCH_TXFLOW;
		if (val & POA_GE_XFC_RX_MSK)
			res |= MTKSWITCH_RXFLOW;
	}

	return (res);
}