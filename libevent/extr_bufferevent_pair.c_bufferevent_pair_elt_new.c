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
struct event_base {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  output; } ;
struct TYPE_4__ {TYPE_1__ bev; } ;
struct bufferevent_pair {TYPE_2__ bev; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_pair_outbuf_cb ; 
 int /*<<< orphan*/  bufferevent_free (int /*<<< orphan*/ ) ; 
 scalar_t__ bufferevent_init_common_ (TYPE_2__*,struct event_base*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bufferevent_init_generic_timeout_cbs_ (TYPE_1__*) ; 
 int /*<<< orphan*/  bufferevent_ops_pair ; 
 int /*<<< orphan*/  downcast (struct bufferevent_pair*) ; 
 int /*<<< orphan*/  evbuffer_add_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bufferevent_pair*) ; 
 struct bufferevent_pair* mm_calloc (int,int) ; 
 int /*<<< orphan*/  mm_free (struct bufferevent_pair*) ; 

__attribute__((used)) static struct bufferevent_pair *
bufferevent_pair_elt_new(struct event_base *base,
    int options)
{
	struct bufferevent_pair *bufev;
	if (! (bufev = mm_calloc(1, sizeof(struct bufferevent_pair))))
		return NULL;
	if (bufferevent_init_common_(&bufev->bev, base, &bufferevent_ops_pair,
		options)) {
		mm_free(bufev);
		return NULL;
	}
	if (!evbuffer_add_cb(bufev->bev.bev.output, be_pair_outbuf_cb, bufev)) {
		bufferevent_free(downcast(bufev));
		return NULL;
	}

	bufferevent_init_generic_timeout_cbs_(&bufev->bev.bev);

	return bufev;
}