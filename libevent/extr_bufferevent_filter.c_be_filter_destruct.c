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
struct bufferevent_filtered {scalar_t__ outbuf_cb; scalar_t__ inbuf_cb; int /*<<< orphan*/  context; int /*<<< orphan*/  (* free_context ) (int /*<<< orphan*/ ) ;} ;
struct bufferevent {int /*<<< orphan*/  output; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVUTIL_ASSERT (struct bufferevent_filtered*) ; 
 int /*<<< orphan*/  evbuffer_remove_cb_entry (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct bufferevent_filtered* upcast (struct bufferevent*) ; 

__attribute__((used)) static void
be_filter_destruct(struct bufferevent *bev)
{
	struct bufferevent_filtered *bevf = upcast(bev);
	EVUTIL_ASSERT(bevf);
	if (bevf->free_context)
		bevf->free_context(bevf->context);

	if (bevf->inbuf_cb)
		evbuffer_remove_cb_entry(bev->input, bevf->inbuf_cb);

	if (bevf->outbuf_cb)
		evbuffer_remove_cb_entry(bev->output, bevf->outbuf_cb);
}