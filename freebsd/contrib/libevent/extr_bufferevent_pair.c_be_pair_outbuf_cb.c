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
struct evbuffer_cb_info {scalar_t__ n_added; scalar_t__ n_deleted; } ;
struct evbuffer {int dummy; } ;
struct bufferevent_pair {struct bufferevent_pair* partner; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_pair_transfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ be_pair_wants_to_talk (struct bufferevent_pair*,struct bufferevent_pair*) ; 
 int /*<<< orphan*/  decref_and_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  downcast (struct bufferevent_pair*) ; 
 int /*<<< orphan*/  incref_and_lock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
be_pair_outbuf_cb(struct evbuffer *outbuf,
    const struct evbuffer_cb_info *info, void *arg)
{
	struct bufferevent_pair *bev_pair = arg;
	struct bufferevent_pair *partner = bev_pair->partner;

	incref_and_lock(downcast(bev_pair));

	if (info->n_added > info->n_deleted && partner) {
		/* We got more data.  If the other side's reading, then
		   hand it over. */
		if (be_pair_wants_to_talk(bev_pair, partner)) {
			be_pair_transfer(downcast(bev_pair), downcast(partner), 0);
		}
	}

	decref_and_unlock(downcast(bev_pair));
}