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

/* Variables and functions */
 int /*<<< orphan*/  if_clone_detach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * t4_cloner ; 
 int /*<<< orphan*/  t4_trace_lock ; 

void
t4_tracer_modunload()
{

	if (t4_cloner != NULL) {
		/*
		 * The module is being unloaded so the nexus drivers have
		 * detached.  The tracing interfaces can not outlive the nexus
		 * (ifp->if_softc is the nexus) and must have been destroyed
		 * already.  XXX: but if_clone is opaque to us and we can't
		 * assert LIST_EMPTY(&t4_cloner->ifc_iflist) at this time.
		 */
		if_clone_detach(t4_cloner);
	}
	sx_destroy(&t4_trace_lock);
}