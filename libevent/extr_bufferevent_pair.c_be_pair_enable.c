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
struct bufferevent_pair {struct bufferevent_pair* partner; } ;
struct bufferevent {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_RESET_GENERIC_READ_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 short EV_READ ; 
 short EV_WRITE ; 
 int /*<<< orphan*/  be_pair_transfer (struct bufferevent*,struct bufferevent*,int /*<<< orphan*/ ) ; 
 scalar_t__ be_pair_wants_to_talk (struct bufferevent_pair*,struct bufferevent_pair*) ; 
 int /*<<< orphan*/  decref_and_unlock (struct bufferevent*) ; 
 struct bufferevent* downcast (struct bufferevent_pair*) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  incref_and_lock (struct bufferevent*) ; 
 struct bufferevent_pair* upcast (struct bufferevent*) ; 

__attribute__((used)) static int
be_pair_enable(struct bufferevent *bufev, short events)
{
	struct bufferevent_pair *bev_p = upcast(bufev);
	struct bufferevent_pair *partner = bev_p->partner;

	incref_and_lock(bufev);

	if (events & EV_READ) {
		BEV_RESET_GENERIC_READ_TIMEOUT(bufev);
	}
	if ((events & EV_WRITE) && evbuffer_get_length(bufev->output))
		BEV_RESET_GENERIC_WRITE_TIMEOUT(bufev);

	/* We're starting to read! Does the other side have anything to write?*/
	if ((events & EV_READ) && partner &&
	    be_pair_wants_to_talk(partner, bev_p)) {
		be_pair_transfer(downcast(partner), bufev, 0);
	}
	/* We're starting to write! Does the other side want to read? */
	if ((events & EV_WRITE) && partner &&
	    be_pair_wants_to_talk(bev_p, partner)) {
		be_pair_transfer(bufev, downcast(partner), 0);
	}
	decref_and_unlock(bufev);
	return 0;
}