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
typedef  int /*<<< orphan*/  u32 ;
struct mps_softc {int /*<<< orphan*/  event_list; } ;
struct mps_event_handle {void* data; int /*<<< orphan*/ * callback; } ;
typedef  int /*<<< orphan*/  mps_evt_callback_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MPS_ERROR ; 
 int /*<<< orphan*/  M_MPT2 ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mps_event_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eh_list ; 
 struct mps_event_handle* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mps_dprint (struct mps_softc*,int /*<<< orphan*/ ,char*) ; 
 int mps_update_events (struct mps_softc*,struct mps_event_handle*,int /*<<< orphan*/ *) ; 

int
mps_register_events(struct mps_softc *sc, u32 *mask,
    mps_evt_callback_t *cb, void *data, struct mps_event_handle **handle)
{
	struct mps_event_handle *eh;
	int error = 0;

	eh = malloc(sizeof(struct mps_event_handle), M_MPT2, M_WAITOK|M_ZERO);
	if(!eh) {
		mps_dprint(sc, MPS_ERROR, "Cannot allocate event memory\n");
		return (ENOMEM);
	}
	eh->callback = cb;
	eh->data = data;
	TAILQ_INSERT_TAIL(&sc->event_list, eh, eh_list);
	if (mask != NULL)
		error = mps_update_events(sc, eh, mask);
	*handle = eh;

	return (error);
}