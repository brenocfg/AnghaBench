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
struct bufferevent_filtered {void (* free_context ) (void*) ;void* outbuf_cb; void* inbuf_cb; struct bufferevent* underlying; void* context; void* process_out; void* process_in; int /*<<< orphan*/  bev; } ;
struct bufferevent {int /*<<< orphan*/  output; int /*<<< orphan*/  input; int /*<<< orphan*/  ev_base; } ;
typedef  void* bufferevent_filter_cb ;

/* Variables and functions */
 int BEV_OPT_THREADSAFE ; 
 int /*<<< orphan*/  BEV_SUSPEND_FILT_READ ; 
 int /*<<< orphan*/  EVBUFFER_CB_ENABLED ; 
 int EV_READ ; 
 int EV_WRITE ; 
 int /*<<< orphan*/  be_filter_eventcb ; 
 int /*<<< orphan*/  be_filter_readcb ; 
 int /*<<< orphan*/  be_filter_writecb ; 
 void* be_null_filter ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int) ; 
 int /*<<< orphan*/  bufferevent_enable_locking_ (struct bufferevent*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bufferevent_filtered_inbuf_cb ; 
 int /*<<< orphan*/  bufferevent_filtered_outbuf_cb ; 
 int /*<<< orphan*/  bufferevent_incref_ (struct bufferevent*) ; 
 scalar_t__ bufferevent_init_common_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bufferevent_init_generic_timeout_cbs_ (struct bufferevent*) ; 
 int /*<<< orphan*/  bufferevent_ops_filter ; 
 int /*<<< orphan*/  bufferevent_setcb (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent_filtered*) ; 
 int /*<<< orphan*/  bufferevent_suspend_read_ (struct bufferevent*,int /*<<< orphan*/ ) ; 
 struct bufferevent* downcast (struct bufferevent_filtered*) ; 
 void* evbuffer_add_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent_filtered*) ; 
 int /*<<< orphan*/  evbuffer_cb_clear_flags (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct bufferevent_filtered* mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct bufferevent_filtered*) ; 

struct bufferevent *
bufferevent_filter_new(struct bufferevent *underlying,
		       bufferevent_filter_cb input_filter,
		       bufferevent_filter_cb output_filter,
		       int options,
		       void (*free_context)(void *),
		       void *ctx)
{
	struct bufferevent_filtered *bufev_f;
	int tmp_options = options & ~BEV_OPT_THREADSAFE;

	if (!underlying)
		return NULL;

	if (!input_filter)
		input_filter = be_null_filter;
	if (!output_filter)
		output_filter = be_null_filter;

	bufev_f = mm_calloc(1, sizeof(struct bufferevent_filtered));
	if (!bufev_f)
		return NULL;

	if (bufferevent_init_common_(&bufev_f->bev, underlying->ev_base,
				    &bufferevent_ops_filter, tmp_options) < 0) {
		mm_free(bufev_f);
		return NULL;
	}
	if (options & BEV_OPT_THREADSAFE) {
		bufferevent_enable_locking_(downcast(bufev_f), NULL);
	}

	bufev_f->underlying = underlying;

	bufev_f->process_in = input_filter;
	bufev_f->process_out = output_filter;
	bufev_f->free_context = free_context;
	bufev_f->context = ctx;

	bufferevent_setcb(bufev_f->underlying,
	    be_filter_readcb, be_filter_writecb, be_filter_eventcb, bufev_f);

	bufev_f->inbuf_cb = evbuffer_add_cb(downcast(bufev_f)->input,
		bufferevent_filtered_inbuf_cb, bufev_f);
	evbuffer_cb_clear_flags(downcast(bufev_f)->input, bufev_f->inbuf_cb,
		EVBUFFER_CB_ENABLED);

	bufev_f->outbuf_cb = evbuffer_add_cb(downcast(bufev_f)->output,
	   bufferevent_filtered_outbuf_cb, bufev_f);

	bufferevent_init_generic_timeout_cbs_(downcast(bufev_f));
	bufferevent_incref_(underlying);

	bufferevent_enable(underlying, EV_READ|EV_WRITE);
	bufferevent_suspend_read_(underlying, BEV_SUSPEND_FILT_READ);

	return downcast(bufev_f);
}