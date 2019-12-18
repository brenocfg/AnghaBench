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
struct event_base {int dummy; } ;
struct bufferevent {int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; int /*<<< orphan*/  enabled; struct bufferevent_ops const* be_ops; int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  timeout_read; struct event_base* ev_base; } ;
struct bufferevent_private {int refcnt; int options; int /*<<< orphan*/  deferred; struct bufferevent bev; } ;
struct bufferevent_ops {int dummy; } ;
typedef  enum bufferevent_options { ____Placeholder_bufferevent_options } bufferevent_options ;

/* Variables and functions */
 int BEV_OPT_DEFER_CALLBACKS ; 
 int BEV_OPT_THREADSAFE ; 
 int BEV_OPT_UNLOCK_CALLBACKS ; 
 int /*<<< orphan*/  EV_WRITE ; 
 scalar_t__ bufferevent_enable_locking_ (struct bufferevent*,int /*<<< orphan*/ *) ; 
 scalar_t__ bufferevent_ratelim_init_ (struct bufferevent_private*) ; 
 int /*<<< orphan*/  bufferevent_run_deferred_callbacks_locked ; 
 int /*<<< orphan*/  bufferevent_run_deferred_callbacks_unlocked ; 
 int /*<<< orphan*/  evbuffer_free (int /*<<< orphan*/ *) ; 
 void* evbuffer_new () ; 
 int /*<<< orphan*/  evbuffer_set_parent_ (int /*<<< orphan*/ *,struct bufferevent*) ; 
 int event_base_get_npriorities (struct event_base*) ; 
 int /*<<< orphan*/  event_deferred_cb_init_ (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct bufferevent_private*) ; 
 int /*<<< orphan*/  event_warnx (char*) ; 
 int /*<<< orphan*/  evutil_timerclear (int /*<<< orphan*/ *) ; 

int
bufferevent_init_common_(struct bufferevent_private *bufev_private,
    struct event_base *base,
    const struct bufferevent_ops *ops,
    enum bufferevent_options options)
{
	struct bufferevent *bufev = &bufev_private->bev;

	if (!bufev->input) {
		if ((bufev->input = evbuffer_new()) == NULL)
			goto err;
	}

	if (!bufev->output) {
		if ((bufev->output = evbuffer_new()) == NULL)
			goto err;
	}

	bufev_private->refcnt = 1;
	bufev->ev_base = base;

	/* Disable timeouts. */
	evutil_timerclear(&bufev->timeout_read);
	evutil_timerclear(&bufev->timeout_write);

	bufev->be_ops = ops;

	if (bufferevent_ratelim_init_(bufev_private))
		goto err;

	/*
	 * Set to EV_WRITE so that using bufferevent_write is going to
	 * trigger a callback.  Reading needs to be explicitly enabled
	 * because otherwise no data will be available.
	 */
	bufev->enabled = EV_WRITE;

#ifndef EVENT__DISABLE_THREAD_SUPPORT
	if (options & BEV_OPT_THREADSAFE) {
		if (bufferevent_enable_locking_(bufev, NULL) < 0)
			goto err;
	}
#endif
	if ((options & (BEV_OPT_DEFER_CALLBACKS|BEV_OPT_UNLOCK_CALLBACKS))
	    == BEV_OPT_UNLOCK_CALLBACKS) {
		event_warnx("UNLOCK_CALLBACKS requires DEFER_CALLBACKS");
		goto err;
	}
	if (options & BEV_OPT_UNLOCK_CALLBACKS)
		event_deferred_cb_init_(
		    &bufev_private->deferred,
		    event_base_get_npriorities(base) / 2,
		    bufferevent_run_deferred_callbacks_unlocked,
		    bufev_private);
	else
		event_deferred_cb_init_(
		    &bufev_private->deferred,
		    event_base_get_npriorities(base) / 2,
		    bufferevent_run_deferred_callbacks_locked,
		    bufev_private);

	bufev_private->options = options;

	evbuffer_set_parent_(bufev->input, bufev);
	evbuffer_set_parent_(bufev->output, bufev);

	return 0;

err:
	if (bufev->input) {
		evbuffer_free(bufev->input);
		bufev->input = NULL;
	}
	if (bufev->output) {
		evbuffer_free(bufev->output);
		bufev->output = NULL;
	}
	return -1;
}