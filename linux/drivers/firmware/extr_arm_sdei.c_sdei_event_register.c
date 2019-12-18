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
typedef  int /*<<< orphan*/  sdei_event_callback ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ IS_ERR (struct sdei_event*) ; 
 int PTR_ERR (struct sdei_event*) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int _sdei_event_register (struct sdei_event*) ; 
 int /*<<< orphan*/  in_nmi () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 struct sdei_event* sdei_event_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sdei_event_destroy (struct sdei_event*) ; 
 scalar_t__ sdei_event_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdei_events_lock ; 

int sdei_event_register(u32 event_num, sdei_event_callback *cb, void *arg)
{
	int err;
	struct sdei_event *event;

	WARN_ON(in_nmi());

	mutex_lock(&sdei_events_lock);
	do {
		if (sdei_event_find(event_num)) {
			pr_warn("Event %u already registered\n", event_num);
			err = -EBUSY;
			break;
		}

		event = sdei_event_create(event_num, cb, arg);
		if (IS_ERR(event)) {
			err = PTR_ERR(event);
			pr_warn("Failed to create event %u: %d\n", event_num,
				err);
			break;
		}

		err = _sdei_event_register(event);
		if (err) {
			sdei_event_destroy(event);
			pr_warn("Failed to register event %u: %d\n", event_num,
				err);
		}
	} while (0);
	mutex_unlock(&sdei_events_lock);

	return err;
}