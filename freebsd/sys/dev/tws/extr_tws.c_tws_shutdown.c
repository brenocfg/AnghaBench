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
struct tws_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tws_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tws_init_connect (struct tws_softc*,int) ; 
 int /*<<< orphan*/  tws_turn_off_interrupts (struct tws_softc*) ; 

__attribute__((used)) static int
tws_shutdown(device_t dev)
{

    struct tws_softc *sc = device_get_softc(dev);

    TWS_TRACE_DEBUG(sc, "entry", 0, 0);

    tws_turn_off_interrupts(sc);
    tws_init_connect(sc, 1);

    return (0);
}