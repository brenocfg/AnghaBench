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
struct timeval {int member_0; int /*<<< orphan*/  member_1; } ;
struct event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_PERSIST ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  delays ; 
 int /*<<< orphan*/  durations ; 
 int /*<<< orphan*/  event_add (struct event*,struct timeval*) ; 
 int /*<<< orphan*/  event_base_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  event_base_new () ; 
 int /*<<< orphan*/  event_free (struct event*) ; 
 struct event* event_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct event* evsignal_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evwatch_check_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evwatch_prepare_new (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  histogram_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  histogram_new (int) ; 
 int /*<<< orphan*/  on_check ; 
 int /*<<< orphan*/  on_prepare ; 
 int /*<<< orphan*/  on_sigint ; 
 int /*<<< orphan*/  on_timeout ; 

int
main(int argc, char **argv)
{
	struct timeval one_second = { 1, 0 };
	struct event *timeout_event, *sigint_event;

	base = event_base_new();
	durations = histogram_new(100);
	delays = histogram_new(100);

	/* add prepare and check watchers; no need to hang on to their pointers,
	 * since they will be freed for us in event_base_free. */
	evwatch_prepare_new(base, &on_prepare, NULL);
	evwatch_check_new(base, &on_check, NULL);

	/* set a persistent one second timeout */
	timeout_event = event_new(base, -1, EV_PERSIST, &on_timeout, NULL);
	if (!timeout_event)
		return EXIT_FAILURE;
	event_add(timeout_event, &one_second);

	/* set a handler for interrupt, so we can quit cleanly */
	sigint_event = evsignal_new(base, SIGINT, &on_sigint, NULL);
	if (!sigint_event)
		return EXIT_FAILURE;
	event_add(sigint_event, NULL);

	/* run the event loop until interrupted */
	event_base_dispatch(base);

	/* clean up */
	event_free(timeout_event);
	event_free(sigint_event);
	event_base_free(base);
	histogram_free(durations);
	histogram_free(delays);

	return EXIT_SUCCESS;
}