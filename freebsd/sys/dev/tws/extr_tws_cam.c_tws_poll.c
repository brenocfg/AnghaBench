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
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWS_TRACE_DEBUG (struct tws_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  tws_intr (void*) ; 

__attribute__((used)) static void
tws_poll(struct cam_sim *sim)
{
    struct tws_softc *sc = (struct tws_softc *)cam_sim_softc(sim);
    TWS_TRACE_DEBUG(sc, "entry", 0, 0);
    tws_intr((void *) sc);
}