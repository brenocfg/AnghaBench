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
struct lro_entry {int /*<<< orphan*/  m_head; } ;
struct lro_ctrl {unsigned int lro_mbuf_count; TYPE_1__* lro_mbuf_data; scalar_t__ lro_hashsz; TYPE_1__* lro_hash; int /*<<< orphan*/  lro_active; int /*<<< orphan*/  lro_free; } ;
struct TYPE_2__ {int /*<<< orphan*/  mb; } ;

/* Variables and functions */
 struct lro_entry* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_LRO ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_lro_active_remove (struct lro_entry*) ; 

void
tcp_lro_free(struct lro_ctrl *lc)
{
	struct lro_entry *le;
	unsigned x;

	/* reset LRO free list */
	LIST_INIT(&lc->lro_free);

	/* free active mbufs, if any */
	while ((le = LIST_FIRST(&lc->lro_active)) != NULL) {
		tcp_lro_active_remove(le);
		m_freem(le->m_head);
	}

	/* free hash table */
	free(lc->lro_hash, M_LRO);
	lc->lro_hash = NULL;
	lc->lro_hashsz = 0;

	/* free mbuf array, if any */
	for (x = 0; x != lc->lro_mbuf_count; x++)
		m_freem(lc->lro_mbuf_data[x].mb);
	lc->lro_mbuf_count = 0;

	/* free allocated memory, if any */
	free(lc->lro_mbuf_data, M_LRO);
	lc->lro_mbuf_data = NULL;
}