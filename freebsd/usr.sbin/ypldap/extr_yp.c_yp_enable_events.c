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
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct yp_event*,int /*<<< orphan*/ ) ; 
 struct yp_event* calloc (int,int) ; 
 TYPE_2__* env ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ *) ; 
 int getdtablesize () ; 
 int /*<<< orphan*/  ye_entry ; 
 int /*<<< orphan*/  yp_fd_event ; 

void
yp_enable_events(void)
{
	int i;
	struct yp_event	*ye;

	for (i = 0; i < getdtablesize(); i++) {
		if ((ye = calloc(1, sizeof(*ye))) == NULL)
			fatal(NULL);
		event_set(&ye->ye_event, i, EV_READ, yp_fd_event, NULL);
		event_add(&ye->ye_event, NULL);
		TAILQ_INSERT_TAIL(&env->sc_yp->yd_events, ye, ye_entry);
	}
}