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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ u_int ;
struct netmap_slot {int flags; scalar_t__ len; int /*<<< orphan*/  buf_idx; } ;
struct netmap_ring {scalar_t__ head; scalar_t__ cur; struct netmap_slot* slot; } ;

/* Variables and functions */
 char* NETMAP_BUF (struct netmap_ring*,int /*<<< orphan*/ ) ; 
 int NS_MOREFRAG ; 
 int /*<<< orphan*/  dump_payload (char*,scalar_t__,struct netmap_ring*,scalar_t__) ; 
 scalar_t__ nm_ring_next (struct netmap_ring*,scalar_t__) ; 
 scalar_t__ nm_ring_space (struct netmap_ring*) ; 

__attribute__((used)) static int
receive_packets(struct netmap_ring *ring, u_int limit, int dump, uint64_t *bytes)
{
	u_int head, rx, n;
	uint64_t b = 0;
	u_int complete = 0;

	if (bytes == NULL)
		bytes = &b;

	head = ring->head;
	n = nm_ring_space(ring);
	if (n < limit)
		limit = n;
	for (rx = 0; rx < limit; rx++) {
		struct netmap_slot *slot = &ring->slot[head];
		char *p = NETMAP_BUF(ring, slot->buf_idx);

		*bytes += slot->len;
		if (dump)
			dump_payload(p, slot->len, ring, head);
		if (!(slot->flags & NS_MOREFRAG))
			complete++;

		head = nm_ring_next(ring, head);
	}
	ring->head = ring->cur = head;

	return (complete);
}