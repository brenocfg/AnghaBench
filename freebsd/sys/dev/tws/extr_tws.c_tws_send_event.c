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
struct tws_softc {int /*<<< orphan*/  tws_state; int /*<<< orphan*/  tws_dev; int /*<<< orphan*/  tws_prev_state; int /*<<< orphan*/  gen_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  TWS_INIT ; 
#define  TWS_INIT_COMPLETE 133 
#define  TWS_INIT_START 132 
 int /*<<< orphan*/  TWS_OFFLINE ; 
 int /*<<< orphan*/  TWS_ONLINE ; 
 int /*<<< orphan*/  TWS_RESET ; 
#define  TWS_RESET_COMPLETE 131 
#define  TWS_RESET_START 130 
#define  TWS_SCAN_FAILURE 129 
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TWS_UNINIT ; 
#define  TWS_UNINIT_START 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
tws_send_event(struct tws_softc *sc, u_int8_t event)
{
    mtx_assert(&sc->gen_lock, MA_OWNED);
    TWS_TRACE_DEBUG(sc, "received event ", 0, event);
    switch (event) {

        case TWS_INIT_START:
            sc->tws_state = TWS_INIT;
            break;

        case TWS_INIT_COMPLETE:
            if (sc->tws_state != TWS_INIT) {
                device_printf(sc->tws_dev, "invalid state transition %d => TWS_ONLINE\n", sc->tws_state);
            } else {
                sc->tws_state = TWS_ONLINE;
            }
            break;

        case TWS_RESET_START:
            /* We can transition to reset state from any state except reset*/ 
            if (sc->tws_state != TWS_RESET) {
                sc->tws_prev_state = sc->tws_state;
                sc->tws_state = TWS_RESET;
            }
            break;

        case TWS_RESET_COMPLETE:
            if (sc->tws_state != TWS_RESET) {
                device_printf(sc->tws_dev, "invalid state transition %d => %d (previous state)\n", sc->tws_state, sc->tws_prev_state);
            } else {
                sc->tws_state = sc->tws_prev_state;
            }
            break;

        case TWS_SCAN_FAILURE:
            if (sc->tws_state != TWS_ONLINE) {
                device_printf(sc->tws_dev, "invalid state transition %d => TWS_OFFLINE\n", sc->tws_state);
            } else {
                sc->tws_state = TWS_OFFLINE;
            }
            break;

        case TWS_UNINIT_START:
            if ((sc->tws_state != TWS_ONLINE) && (sc->tws_state != TWS_OFFLINE)) {
                device_printf(sc->tws_dev, "invalid state transition %d => TWS_UNINIT\n", sc->tws_state);
            } else {
                sc->tws_state = TWS_UNINIT;
            }
            break;
    }

}