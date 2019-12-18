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
struct aac_softc {int /*<<< orphan*/  aac_dev; int /*<<< orphan*/  aac_ev_cmfree; } ;
struct aac_event {int ev_type; } ;

/* Variables and functions */
#define  AAC_EVENT_CMFREE 128 
 int AAC_EVENT_MASK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct aac_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ev_links ; 

void
aacraid_add_event(struct aac_softc *sc, struct aac_event *event)
{

	switch (event->ev_type & AAC_EVENT_MASK) {
	case AAC_EVENT_CMFREE:
		TAILQ_INSERT_TAIL(&sc->aac_ev_cmfree, event, ev_links);
		break;
	default:
		device_printf(sc->aac_dev, "aac_add event: unknown event %d\n",
		    event->ev_type);
		break;
	}

	return;
}