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
struct mps_softc {int /*<<< orphan*/  event_list; } ;
struct mps_event_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_MPT2 ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct mps_event_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eh_list ; 
 int /*<<< orphan*/  free (struct mps_event_handle*,int /*<<< orphan*/ ) ; 

void
mps_deregister_events(struct mps_softc *sc, struct mps_event_handle *handle)
{

	TAILQ_REMOVE(&sc->event_list, handle, eh_list);
	free(handle, M_MPT2);
}