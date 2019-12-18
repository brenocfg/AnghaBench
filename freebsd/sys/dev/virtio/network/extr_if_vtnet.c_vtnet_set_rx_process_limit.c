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
struct vtnet_softc {int vtnet_rx_process_limit; } ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  vtnet_rx_process_limit ; 
 int vtnet_tunable_int (struct vtnet_softc*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtnet_set_rx_process_limit(struct vtnet_softc *sc)
{
	int limit;

	limit = vtnet_tunable_int(sc, "rx_process_limit",
	    vtnet_rx_process_limit);
	if (limit < 0)
		limit = INT_MAX;
	sc->vtnet_rx_process_limit = limit;
}