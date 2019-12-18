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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct l2t_entry {scalar_t__ state; scalar_t__ vlan; scalar_t__ lport; size_t hash; struct l2t_entry* next; struct l2t_entry* first; int /*<<< orphan*/  dmac; int /*<<< orphan*/  refcnt; } ;
struct l2t_data {size_t l2t_size; struct l2t_entry* l2tab; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 scalar_t__ L2T_STATE_SWITCHING ; 
 scalar_t__ L2T_STATE_UNUSED ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct l2t_entry *
find_or_alloc_l2e(struct l2t_data *d, uint16_t vlan, uint8_t port, uint8_t *dmac)
{
	struct l2t_entry *end, *e, **p;
	struct l2t_entry *first_free = NULL;

	for (e = &d->l2tab[0], end = &d->l2tab[d->l2t_size]; e != end; ++e) {
		if (atomic_load_acq_int(&e->refcnt) == 0) {
			if (!first_free)
				first_free = e;
		} else if (e->state == L2T_STATE_SWITCHING &&
		    memcmp(e->dmac, dmac, ETHER_ADDR_LEN) == 0 &&
		    e->vlan == vlan && e->lport == port)
			return (e);	/* Found existing entry that matches. */
	}

	if (first_free == NULL)
		return (NULL);	/* No match and no room for a new entry. */

	/*
	 * The entry we found may be an inactive entry that is
	 * presently in the hash table.  We need to remove it.
	 */
	e = first_free;
	if (e->state < L2T_STATE_SWITCHING) {
		for (p = &d->l2tab[e->hash].first; *p; p = &(*p)->next) {
			if (*p == e) {
				*p = e->next;
				e->next = NULL;
				break;
			}
		}
	}
	e->state = L2T_STATE_UNUSED;
	return (e);
}