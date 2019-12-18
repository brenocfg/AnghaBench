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
struct Ignore_Event {int sequence; int response_type; int /*<<< orphan*/  added; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct Ignore_Event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_events ; 
 struct Ignore_Event* smalloc (int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void add_ignore_event(const int sequence, const int response_type) {
    struct Ignore_Event *event = smalloc(sizeof(struct Ignore_Event));

    event->sequence = sequence;
    event->response_type = response_type;
    event->added = time(NULL);

    SLIST_INSERT_HEAD(&ignore_events, event, ignore_events);
}