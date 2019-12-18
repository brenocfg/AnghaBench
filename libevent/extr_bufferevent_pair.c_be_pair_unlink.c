#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bufferevent_pair {TYPE_1__* partner; TYPE_1__* unlinked_partner; } ;
struct bufferevent {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * partner; } ;

/* Variables and functions */
 struct bufferevent_pair* upcast (struct bufferevent*) ; 

__attribute__((used)) static void
be_pair_unlink(struct bufferevent *bev)
{
	struct bufferevent_pair *bev_p = upcast(bev);

	if (bev_p->partner) {
		bev_p->unlinked_partner = bev_p->partner;
		bev_p->partner->partner = NULL;
		bev_p->partner = NULL;
	}
}