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
typedef  int /*<<< orphan*/  uint8_t ;
struct mpr_softc {int /*<<< orphan*/  event_list; } ;
struct mpr_event_handle {void* data; int /*<<< orphan*/ * callback; } ;
typedef  int /*<<< orphan*/  mpr_evt_callback_t ;

/* Variables and functions */
 int ENOMEM ; 
 int MPR_ERROR ; 
 int MPR_EVENT ; 
 int /*<<< orphan*/  M_MPR ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct mpr_event_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eh_list ; 
 struct mpr_event_handle* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mpr_dprint (struct mpr_softc*,int,char*) ; 
 int mpr_update_events (struct mpr_softc*,struct mpr_event_handle*,int /*<<< orphan*/ *) ; 

int
mpr_register_events(struct mpr_softc *sc, uint8_t *mask,
    mpr_evt_callback_t *cb, void *data, struct mpr_event_handle **handle)
{
	struct mpr_event_handle *eh;
	int error = 0;

	eh = malloc(sizeof(struct mpr_event_handle), M_MPR, M_WAITOK|M_ZERO);
	if (!eh) {
		mpr_dprint(sc, MPR_EVENT|MPR_ERROR,
		    "Cannot allocate event memory\n");
		return (ENOMEM);
	}
	eh->callback = cb;
	eh->data = data;
	TAILQ_INSERT_TAIL(&sc->event_list, eh, eh_list);
	if (mask != NULL)
		error = mpr_update_events(sc, eh, mask);
	*handle = eh;

	return (error);
}