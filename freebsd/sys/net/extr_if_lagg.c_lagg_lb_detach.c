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
struct lagg_softc {scalar_t__ sc_psc; } ;
struct lagg_lb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_LAGG ; 
 int /*<<< orphan*/  free (struct lagg_lb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lagg_lb_detach(struct lagg_softc *sc)
{
	struct lagg_lb *lb;

	lb = (struct lagg_lb *)sc->sc_psc;
	if (lb != NULL)
		free(lb, M_LAGG);
}