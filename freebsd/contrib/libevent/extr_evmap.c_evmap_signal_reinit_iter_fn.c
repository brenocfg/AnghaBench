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
struct evmap_signal {int /*<<< orphan*/  events; } ;
struct eventop {int (* add ) (struct event_base*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct event_base {struct eventop* evsigsel; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SIGNAL ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int stub1 (struct event_base*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evmap_signal_reinit_iter_fn(struct event_base *base,
    int signum, struct evmap_signal *ctx, void *arg)
{
	const struct eventop *evsel = base->evsigsel;
	int *result = arg;

	if (!LIST_EMPTY(&ctx->events)) {
		if (evsel->add(base, signum, 0, EV_SIGNAL, NULL) == -1)
			*result = -1;
	}
	return 0;
}