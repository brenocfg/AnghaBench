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
typedef  size_t lagg_proto ;
struct TYPE_2__ {int /*<<< orphan*/  (* pr_detach ) (struct lagg_softc*) ;} ;

/* Variables and functions */
 size_t LAGG_PROTO_NONE ; 
 int /*<<< orphan*/  LAGG_XLOCK_ASSERT (struct lagg_softc*) ; 
 TYPE_1__* lagg_protos ; 
 int /*<<< orphan*/  stub1 (struct lagg_softc*) ; 

__attribute__((used)) static void
lagg_proto_detach(struct lagg_softc *sc)
{
	lagg_proto pr;

	LAGG_XLOCK_ASSERT(sc);
	pr = sc->sc_proto;
	sc->sc_proto = LAGG_PROTO_NONE;

	if (lagg_protos[pr].pr_detach != NULL)
		lagg_protos[pr].pr_detach(sc);
}