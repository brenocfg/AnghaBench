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
struct lagg_softc {size_t sc_proto; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pr_stop ) (struct lagg_softc*) ;} ;

/* Variables and functions */
 TYPE_1__* lagg_protos ; 
 int /*<<< orphan*/  stub1 (struct lagg_softc*) ; 

__attribute__((used)) static void
lagg_proto_stop(struct lagg_softc *sc)
{

	if (lagg_protos[sc->sc_proto].pr_stop != NULL)
		lagg_protos[sc->sc_proto].pr_stop(sc);
}