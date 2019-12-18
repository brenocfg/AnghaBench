#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ own_lock; } ;
struct bufferevent_pair {TYPE_3__* unlinked_partner; TYPE_2__ bev; } ;
struct bufferevent {int dummy; } ;
struct TYPE_4__ {int own_lock; } ;
struct TYPE_6__ {TYPE_1__ bev; } ;

/* Variables and functions */
 struct bufferevent_pair* upcast (struct bufferevent*) ; 

__attribute__((used)) static void
be_pair_destruct(struct bufferevent *bev)
{
	struct bufferevent_pair *bev_p = upcast(bev);

	/* Transfer ownership of the lock into partner, otherwise we will use
	 * already free'd lock during freeing second bev, see next example:
	 *
	 * bev1->own_lock = 1
	 * bev2->own_lock = 0
	 * bev2->lock = bev1->lock
	 *
	 * bufferevent_free(bev1) # refcnt == 0 -> unlink
	 * bufferevent_free(bev2) # refcnt == 0 -> unlink
	 *
	 * event_base_free() -> finilizers -> EVTHREAD_FREE_LOCK(bev1->lock)
	 *                                 -> BEV_LOCK(bev2->lock) <-- already freed
	 *
	 * Where bev1 == pair[0], bev2 == pair[1].
	 */
	if (bev_p->unlinked_partner && bev_p->bev.own_lock) {
		bev_p->unlinked_partner->bev.own_lock = 1;
		bev_p->bev.own_lock = 0;
	}
	bev_p->unlinked_partner = NULL;
}