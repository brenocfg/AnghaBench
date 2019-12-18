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
struct sdei_event {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int _sdei_event_unregister (struct sdei_event*) ; 
 int /*<<< orphan*/  in_nmi () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdei_event_destroy (struct sdei_event*) ; 
 struct sdei_event* sdei_event_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdei_events_lock ; 

int sdei_event_unregister(u32 event_num)
{
	int err;
	struct sdei_event *event;

	WARN_ON(in_nmi());

	mutex_lock(&sdei_events_lock);
	event = sdei_event_find(event_num);
	do {
		if (!event) {
			pr_warn("Event %u not registered\n", event_num);
			err = -ENOENT;
			break;
		}

		err = _sdei_event_unregister(event);
		if (err)
			break;

		sdei_event_destroy(event);
	} while (0);
	mutex_unlock(&sdei_events_lock);

	return err;
}