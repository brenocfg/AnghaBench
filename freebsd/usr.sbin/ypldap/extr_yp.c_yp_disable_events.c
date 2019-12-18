#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct yp_event {int /*<<< orphan*/  ye_event; } ;
struct TYPE_4__ {TYPE_1__* sc_yp; } ;
struct TYPE_3__ {int /*<<< orphan*/  yd_events; } ;

/* Variables and functions */
 struct yp_event* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct yp_event*,int /*<<< orphan*/ ) ; 
 TYPE_2__* env ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct yp_event*) ; 
 int /*<<< orphan*/  ye_entry ; 

void
yp_disable_events(void)
{
	struct yp_event	*ye;

	while ((ye = TAILQ_FIRST(&env->sc_yp->yd_events)) != NULL) {
		TAILQ_REMOVE(&env->sc_yp->yd_events, ye, ye_entry);
		event_del(&ye->ye_event);
		free(ye);
	}
}