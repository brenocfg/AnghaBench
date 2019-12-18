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
struct netmap_slot {int flags; } ;
struct netmap_ring {unsigned int tail; struct netmap_slot* slot; } ;
struct netmap_kring {scalar_t__ nkr_num_slots; struct netmap_ring* ring; } ;

/* Variables and functions */
 int NS_MOREFRAG ; 
 unsigned int nm_next (unsigned int,scalar_t__) ; 

__attribute__((used)) static unsigned int
ptnet_rx_discard(struct netmap_kring *kring, unsigned int head)
{
	struct netmap_ring *ring = kring->ring;
	struct netmap_slot *slot = ring->slot + head;

	for (;;) {
		head = nm_next(head, kring->nkr_num_slots - 1);
		if (!(slot->flags & NS_MOREFRAG) || head == ring->tail) {
			break;
		}
		slot = ring->slot + head;
	}

	return head;
}