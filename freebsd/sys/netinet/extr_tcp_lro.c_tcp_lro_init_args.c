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
struct lro_mbuf_sort {int dummy; } ;
struct lro_entry {int dummy; } ;
struct lro_ctrl {unsigned int lro_mbuf_max; unsigned int lro_cnt; int /*<<< orphan*/  lro_free; struct lro_mbuf_sort* lro_mbuf_data; int /*<<< orphan*/ * lro_hash; int /*<<< orphan*/  lro_hashsz; int /*<<< orphan*/  lro_active; struct ifnet* ifp; int /*<<< orphan*/  lro_length_lim; int /*<<< orphan*/  lro_ackcnt_lim; scalar_t__ lro_mbuf_count; scalar_t__ lro_flushed; scalar_t__ lro_queued; scalar_t__ lro_bad_csum; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HASH_NOWAIT ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct lro_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_LRO ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TCP_LRO_ACKCNT_MAX ; 
 int /*<<< orphan*/  TCP_LRO_LENGTH_MAX ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct lro_ctrl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/ * phashinit_flags (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
tcp_lro_init_args(struct lro_ctrl *lc, struct ifnet *ifp,
    unsigned lro_entries, unsigned lro_mbufs)
{
	struct lro_entry *le;
	size_t size;
	unsigned i, elements;

	lc->lro_bad_csum = 0;
	lc->lro_queued = 0;
	lc->lro_flushed = 0;
	lc->lro_mbuf_count = 0;
	lc->lro_mbuf_max = lro_mbufs;
	lc->lro_cnt = lro_entries;
	lc->lro_ackcnt_lim = TCP_LRO_ACKCNT_MAX;
	lc->lro_length_lim = TCP_LRO_LENGTH_MAX;
	lc->ifp = ifp;
	LIST_INIT(&lc->lro_free);
	LIST_INIT(&lc->lro_active);

	/* create hash table to accelerate entry lookup */
	if (lro_entries > lro_mbufs)
		elements = lro_entries;
	else
		elements = lro_mbufs;
	lc->lro_hash = phashinit_flags(elements, M_LRO, &lc->lro_hashsz,
	    HASH_NOWAIT);
	if (lc->lro_hash == NULL) {
		memset(lc, 0, sizeof(*lc));
		return (ENOMEM);
	}

	/* compute size to allocate */
	size = (lro_mbufs * sizeof(struct lro_mbuf_sort)) +
	    (lro_entries * sizeof(*le));
	lc->lro_mbuf_data = (struct lro_mbuf_sort *)
	    malloc(size, M_LRO, M_NOWAIT | M_ZERO);

	/* check for out of memory */
	if (lc->lro_mbuf_data == NULL) {
		free(lc->lro_hash, M_LRO);
		memset(lc, 0, sizeof(*lc));
		return (ENOMEM);
	}
	/* compute offset for LRO entries */
	le = (struct lro_entry *)
	    (lc->lro_mbuf_data + lro_mbufs);

	/* setup linked list */
	for (i = 0; i != lro_entries; i++)
		LIST_INSERT_HEAD(&lc->lro_free, le + i, next);

	return (0);
}