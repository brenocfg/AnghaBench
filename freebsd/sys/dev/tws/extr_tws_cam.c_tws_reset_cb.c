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
typedef  int u_int32_t ;
typedef  scalar_t__ time_t ;
struct tws_softc {int /*<<< orphan*/  tws_dev; } ;

/* Variables and functions */
 int TWS_BIT13 ; 
 int /*<<< orphan*/  TWS_I2O0_SCRPD3 ; 
 scalar_t__ TWS_LOCAL_TIME ; 
 scalar_t__ TWS_POLL_TIMEOUT ; 
 scalar_t__ TWS_RESET ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tws_drain_busy_queue (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_drain_reserved_reqs (struct tws_softc*) ; 
 int /*<<< orphan*/  tws_drain_response_queue (struct tws_softc*) ; 
 scalar_t__ tws_get_state (struct tws_softc*) ; 
 int tws_read_reg (struct tws_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tws_reset_cb(void *arg)
{
    struct tws_softc *sc = (struct tws_softc *)arg;
    time_t endt;
    int found = 0;
    u_int32_t reg;
  
    if ( tws_get_state(sc) != TWS_RESET ) {
        return;
    }

//  device_printf(sc->tws_dev,  "Draining Busy Queue\n");
    tws_drain_busy_queue(sc);
//  device_printf(sc->tws_dev,  "Draining Reserved Reqs\n");
    tws_drain_reserved_reqs(sc);
//  device_printf(sc->tws_dev,  "Draining Response Queue\n");
    tws_drain_response_queue(sc);

//  device_printf(sc->tws_dev,  "Looking for controller ready flag...\n");
    endt = TWS_LOCAL_TIME + TWS_POLL_TIMEOUT;
    while ((TWS_LOCAL_TIME <= endt) && (!found)) {
        reg = tws_read_reg(sc, TWS_I2O0_SCRPD3, 4);
        if ( reg & TWS_BIT13 ) {
            found = 1;
//          device_printf(sc->tws_dev,  " ... Got it!\n");
        }
    }
    if ( !found )
            device_printf(sc->tws_dev,  " ... Controller ready flag NOT found!\n");
}