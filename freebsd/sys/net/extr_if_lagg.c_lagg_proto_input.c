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
struct mbuf {int dummy; } ;
struct lagg_softc {size_t sc_proto; } ;
struct lagg_port {int dummy; } ;
struct TYPE_2__ {struct mbuf* (* pr_input ) (struct lagg_softc*,struct lagg_port*,struct mbuf*) ;} ;

/* Variables and functions */
 TYPE_1__* lagg_protos ; 
 struct mbuf* stub1 (struct lagg_softc*,struct lagg_port*,struct mbuf*) ; 

__attribute__((used)) static struct mbuf *
lagg_proto_input(struct lagg_softc *sc, struct lagg_port *lp, struct mbuf *m)
{

	return (lagg_protos[sc->sc_proto].pr_input(sc, lp, m));
}