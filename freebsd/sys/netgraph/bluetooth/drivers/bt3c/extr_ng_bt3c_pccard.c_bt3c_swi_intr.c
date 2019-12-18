#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
typedef  TYPE_1__* bt3c_softc_p ;
struct TYPE_3__ {int status; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT3C_ANTENNA_OUT ; 
 int /*<<< orphan*/  NG_BT3C_ALERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NG_BT3C_INFO (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  bt3c_forward ; 
 int /*<<< orphan*/  bt3c_read (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  bt3c_send ; 
 scalar_t__ ng_send_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
bt3c_swi_intr(void *context)
{
	bt3c_softc_p	sc = (bt3c_softc_p) context;
	u_int16_t	data;

	/* Receive complete */
	if (sc->status & 0x0001) {
		sc->status &= ~0x0001; /* XXX is it safe? */

		if (ng_send_fn(sc->node, NULL, &bt3c_forward, NULL, 0) != 0)
			NG_BT3C_ALERT(sc->dev, "Could not forward frames!\n");
	}

	/* Send complete */
	if (sc->status & 0x0002) {
		sc->status &= ~0x0002; /* XXX is it safe */

		if (ng_send_fn(sc->node, NULL, &bt3c_send, NULL, 1) != 0)
			NG_BT3C_ALERT(sc->dev, "Could not send frames!\n");
	}

	/* Antenna position */
	if (sc->status & 0x0020) { 
		sc->status &= ~0x0020; /* XXX is it safe */

		bt3c_read(sc, 0x7002, data);
		data &= 0x10;

		if (data)
			sc->flags |= BT3C_ANTENNA_OUT;
		else
			sc->flags &= ~BT3C_ANTENNA_OUT;

		NG_BT3C_INFO(sc->dev, "Antenna %s\n", data? "OUT" : "IN");
	}
}