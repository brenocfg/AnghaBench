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
struct g_raid3_softc {int /*<<< orphan*/  sc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int G_RAID3_EVENT_DEVICE ; 
 int G_RAID3_EVENT_DONTWAIT ; 
 int /*<<< orphan*/  g_raid3_event_send (struct g_raid3_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_raid3_go(void *arg)
{
	struct g_raid3_softc *sc;

	sc = arg;
	G_RAID3_DEBUG(0, "Force device %s start due to timeout.", sc->sc_name);
	g_raid3_event_send(sc, 0,
	    G_RAID3_EVENT_DONTWAIT | G_RAID3_EVENT_DEVICE);
}