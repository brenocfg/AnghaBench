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
struct timeval {int dummy; } ;
struct event_once {void (* cb ) (int,short,void*) ;int /*<<< orphan*/  ev; void* arg; } ;

/* Variables and functions */
 short EV_READ ; 
 short EV_SIGNAL ; 
 short EV_TIMEOUT ; 
 short EV_WRITE ; 
 struct event_once* calloc (int,int) ; 
 int event_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  event_once_cb ; 
 int /*<<< orphan*/  event_set (int /*<<< orphan*/ *,int,short,int /*<<< orphan*/ ,struct event_once*) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct event_once*) ; 
 int /*<<< orphan*/  free (struct event_once*) ; 
 int /*<<< orphan*/  timerclear (struct timeval*) ; 

int
event_once(int fd, short events,
    void (*callback)(int, short, void *), void *arg, struct timeval *tv)
{
	struct event_once *eonce;
	struct timeval etv;
	int res;

	/* We cannot support signals that just fire once */
	if (events & EV_SIGNAL)
		return (-1);

	if ((eonce = calloc(1, sizeof(struct event_once))) == NULL)
		return (-1);

	eonce->cb = callback;
	eonce->arg = arg;

	if (events == EV_TIMEOUT) {
		if (tv == NULL) {
			timerclear(&etv);
			tv = &etv;
		}

		evtimer_set(&eonce->ev, event_once_cb, eonce);
	} else if (events & (EV_READ|EV_WRITE)) {
		events &= EV_READ|EV_WRITE;

		event_set(&eonce->ev, fd, events, event_once_cb, eonce);
	} else {
		/* Bad event combination */
		free(eonce);
		return (-1);
	}

	res = event_add(&eonce->ev, tv);
	if (res != 0) {
		free(eonce);
		return (res);
	}

	return (0);
}