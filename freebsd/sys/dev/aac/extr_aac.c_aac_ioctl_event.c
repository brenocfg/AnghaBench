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
struct aac_softc {int /*<<< orphan*/  aac_io_lock; } ;
struct aac_event {int ev_type; } ;
struct aac_command {int dummy; } ;

/* Variables and functions */
#define  AAC_EVENT_CMFREE 128 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_AACBUF ; 
 int /*<<< orphan*/  aac_add_event (struct aac_softc*,struct aac_event*) ; 
 int /*<<< orphan*/  aac_alloc_command (struct aac_softc*,struct aac_command**) ; 
 int /*<<< orphan*/  free (struct aac_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (void*) ; 

__attribute__((used)) static void
aac_ioctl_event(struct aac_softc *sc, struct aac_event *event, void *arg)
{

	switch (event->ev_type) {
	case AAC_EVENT_CMFREE:
		mtx_assert(&sc->aac_io_lock, MA_OWNED);
		if (aac_alloc_command(sc, (struct aac_command **)arg)) {
			aac_add_event(sc, event);
			return;
		}
		free(event, M_AACBUF);
		wakeup(arg);
		break;
	default:
		break;
	}
}