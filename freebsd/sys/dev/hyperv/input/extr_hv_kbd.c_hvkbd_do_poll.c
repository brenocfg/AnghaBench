#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  hs_chan; } ;
typedef  TYPE_1__ hv_kbd_sc ;

/* Variables and functions */
 int /*<<< orphan*/  hv_kbd_prod_is_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  hv_kbd_read_channel (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
hvkbd_do_poll(hv_kbd_sc *sc, uint8_t wait)
{
	while (!hv_kbd_prod_is_ready(sc)) {
		hv_kbd_read_channel(sc->hs_chan, sc);
		if (!wait)
			break;
	}
}