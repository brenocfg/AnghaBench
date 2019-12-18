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
struct lagg_port {int dummy; } ;
struct TYPE_2__ {int (* pr_addport ) (struct lagg_port*) ;} ;

/* Variables and functions */
 TYPE_1__* lagg_protos ; 
 int stub1 (struct lagg_port*) ; 

__attribute__((used)) static int
lagg_proto_addport(struct lagg_softc *sc, struct lagg_port *lp)
{

	if (lagg_protos[sc->sc_proto].pr_addport == NULL)
		return (0);
	else
		return (lagg_protos[sc->sc_proto].pr_addport(lp));
}