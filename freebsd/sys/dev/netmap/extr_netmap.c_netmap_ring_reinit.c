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
typedef  scalar_t__ u_int ;
struct netmap_ring {scalar_t__ head; scalar_t__ cur; scalar_t__ tail; TYPE_2__* slot; } ;
struct netmap_kring {scalar_t__ nkr_num_slots; scalar_t__ rhead; scalar_t__ rcur; scalar_t__ rtail; scalar_t__ nr_hwcur; scalar_t__ nr_hwtail; int /*<<< orphan*/  name; TYPE_3__* na; struct netmap_ring* ring; } ;
struct TYPE_4__ {scalar_t__ objtotal; } ;
struct TYPE_6__ {TYPE_1__ na_lut; } ;
struct TYPE_5__ {scalar_t__ buf_idx; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ NETMAP_BUF_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  nm_prlim (int,char*,scalar_t__,...) ; 

int
netmap_ring_reinit(struct netmap_kring *kring)
{
	struct netmap_ring *ring = kring->ring;
	u_int i, lim = kring->nkr_num_slots - 1;
	int errors = 0;

	// XXX KASSERT nm_kr_tryget
	nm_prlim(10, "called for %s", kring->name);
	// XXX probably wrong to trust userspace
	kring->rhead = ring->head;
	kring->rcur  = ring->cur;
	kring->rtail = ring->tail;

	if (ring->cur > lim)
		errors++;
	if (ring->head > lim)
		errors++;
	if (ring->tail > lim)
		errors++;
	for (i = 0; i <= lim; i++) {
		u_int idx = ring->slot[i].buf_idx;
		u_int len = ring->slot[i].len;
		if (idx < 2 || idx >= kring->na->na_lut.objtotal) {
			nm_prlim(5, "bad index at slot %d idx %d len %d ", i, idx, len);
			ring->slot[i].buf_idx = 0;
			ring->slot[i].len = 0;
		} else if (len > NETMAP_BUF_SIZE(kring->na)) {
			ring->slot[i].len = 0;
			nm_prlim(5, "bad len at slot %d idx %d len %d", i, idx, len);
		}
	}
	if (errors) {
		nm_prlim(10, "total %d errors", errors);
		nm_prlim(10, "%s reinit, cur %d -> %d tail %d -> %d",
			kring->name,
			ring->cur, kring->nr_hwcur,
			ring->tail, kring->nr_hwtail);
		ring->head = kring->rhead = kring->nr_hwcur;
		ring->cur  = kring->rcur  = kring->nr_hwcur;
		ring->tail = kring->rtail = kring->nr_hwtail;
	}
	return (errors ? 1 : 0);
}