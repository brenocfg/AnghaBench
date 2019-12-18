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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  u_short ;
struct pf_frent {int fe_len; scalar_t__ fe_off; int /*<<< orphan*/  fe_m; scalar_t__ fe_mff; } ;
struct pf_fragment_cmp {scalar_t__ frc_af; int /*<<< orphan*/  frc_id; } ;
struct pf_fragment {int fr_maxlen; int fr_holes; int /*<<< orphan*/  fr_queue; int /*<<< orphan*/  fr_timeout; int /*<<< orphan*/  fr_entries; int /*<<< orphan*/  fr_firstoff; } ;
struct TYPE_2__ {scalar_t__ fe_off; scalar_t__ fe_len; int /*<<< orphan*/  fe_mff; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  DPFPRINTF (char*) ; 
 scalar_t__ IP_MAXPACKET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PFRES_FRAG ; 
 int /*<<< orphan*/  PFRES_MEMORY ; 
 int /*<<< orphan*/  PF_FRAG_ASSERT () ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pf_fragment*) ; 
 int /*<<< orphan*/  REASON_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct pf_frent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pf_fragment*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pf_frent* TAILQ_NEXT (struct pf_frent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_frag_tree ; 
 int /*<<< orphan*/  V_pf_frag_z ; 
 int /*<<< orphan*/  V_pf_fragqueue ; 
 int /*<<< orphan*/  V_pf_frent_z ; 
 int /*<<< orphan*/  fr_next ; 
 int /*<<< orphan*/  frag_next ; 
 int /*<<< orphan*/  m_adj (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct pf_fragment* pf_find_fragment (struct pf_fragment_cmp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_flush_fragments () ; 
 int /*<<< orphan*/  pf_frag_tree ; 
 int /*<<< orphan*/  pf_fragq ; 
 scalar_t__ pf_frent_insert (struct pf_fragment*,struct pf_frent*,struct pf_frent*) ; 
 struct pf_frent* pf_frent_previous (struct pf_fragment*,struct pf_frent*) ; 
 int /*<<< orphan*/  pf_frent_remove (struct pf_fragment*,struct pf_frent*) ; 
 int /*<<< orphan*/  time_uptime ; 
 struct pf_fragment* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct pf_frent*) ; 

__attribute__((used)) static struct pf_fragment *
pf_fillup_fragment(struct pf_fragment_cmp *key, struct pf_frent *frent,
    u_short *reason)
{
	struct pf_frent		*after, *next, *prev;
	struct pf_fragment	*frag;
	uint16_t		total;

	PF_FRAG_ASSERT();

	/* No empty fragments. */
	if (frent->fe_len == 0) {
		DPFPRINTF(("bad fragment: len 0"));
		goto bad_fragment;
	}

	/* All fragments are 8 byte aligned. */
	if (frent->fe_mff && (frent->fe_len & 0x7)) {
		DPFPRINTF(("bad fragment: mff and len %d", frent->fe_len));
		goto bad_fragment;
	}

	/* Respect maximum length, IP_MAXPACKET == IPV6_MAXPACKET. */
	if (frent->fe_off + frent->fe_len > IP_MAXPACKET) {
		DPFPRINTF(("bad fragment: max packet %d",
		    frent->fe_off + frent->fe_len));
		goto bad_fragment;
	}

	DPFPRINTF((key->frc_af == AF_INET ?
	    "reass frag %d @ %d-%d" : "reass frag %#08x @ %d-%d",
	    key->frc_id, frent->fe_off, frent->fe_off + frent->fe_len));

	/* Fully buffer all of the fragments in this fragment queue. */
	frag = pf_find_fragment(key, &V_pf_frag_tree);

	/* Create a new reassembly queue for this packet. */
	if (frag == NULL) {
		frag = uma_zalloc(V_pf_frag_z, M_NOWAIT);
		if (frag == NULL) {
			pf_flush_fragments();
			frag = uma_zalloc(V_pf_frag_z, M_NOWAIT);
			if (frag == NULL) {
				REASON_SET(reason, PFRES_MEMORY);
				goto drop_fragment;
			}
		}

		*(struct pf_fragment_cmp *)frag = *key;
		memset(frag->fr_firstoff, 0, sizeof(frag->fr_firstoff));
		memset(frag->fr_entries, 0, sizeof(frag->fr_entries));
		frag->fr_timeout = time_uptime;
		frag->fr_maxlen = frent->fe_len;
		frag->fr_holes = 1;
		TAILQ_INIT(&frag->fr_queue);

		RB_INSERT(pf_frag_tree, &V_pf_frag_tree, frag);
		TAILQ_INSERT_HEAD(&V_pf_fragqueue, frag, frag_next);

		/* We do not have a previous fragment, cannot fail. */
		pf_frent_insert(frag, frent, NULL);

		return (frag);
	}

	KASSERT(!TAILQ_EMPTY(&frag->fr_queue), ("!TAILQ_EMPTY()->fr_queue"));

	/* Remember maximum fragment len for refragmentation. */
	if (frent->fe_len > frag->fr_maxlen)
		frag->fr_maxlen = frent->fe_len;

	/* Maximum data we have seen already. */
	total = TAILQ_LAST(&frag->fr_queue, pf_fragq)->fe_off +
		TAILQ_LAST(&frag->fr_queue, pf_fragq)->fe_len;

	/* Non terminal fragments must have more fragments flag. */
	if (frent->fe_off + frent->fe_len < total && !frent->fe_mff)
		goto bad_fragment;

	/* Check if we saw the last fragment already. */
	if (!TAILQ_LAST(&frag->fr_queue, pf_fragq)->fe_mff) {
		if (frent->fe_off + frent->fe_len > total ||
		    (frent->fe_off + frent->fe_len == total && frent->fe_mff))
			goto bad_fragment;
	} else {
		if (frent->fe_off + frent->fe_len == total && !frent->fe_mff)
			goto bad_fragment;
	}

	/* Find neighbors for newly inserted fragment */
	prev = pf_frent_previous(frag, frent);
	if (prev == NULL) {
		after = TAILQ_FIRST(&frag->fr_queue);
		KASSERT(after != NULL, ("after != NULL"));
	} else {
		after = TAILQ_NEXT(prev, fr_next);
	}

	if (prev != NULL && prev->fe_off + prev->fe_len > frent->fe_off) {
		uint16_t precut;

		precut = prev->fe_off + prev->fe_len - frent->fe_off;
		if (precut >= frent->fe_len)
			goto bad_fragment;
		DPFPRINTF(("overlap -%d", precut));
		m_adj(frent->fe_m, precut);
		frent->fe_off += precut;
		frent->fe_len -= precut;
	}

	for (; after != NULL && frent->fe_off + frent->fe_len > after->fe_off;
	    after = next) {
		uint16_t aftercut;

		aftercut = frent->fe_off + frent->fe_len - after->fe_off;
		DPFPRINTF(("adjust overlap %d", aftercut));
		if (aftercut < after->fe_len) {
			m_adj(after->fe_m, aftercut);
			after->fe_off += aftercut;
			after->fe_len -= aftercut;
			break;
		}

		/* This fragment is completely overlapped, lose it. */
		next = TAILQ_NEXT(after, fr_next);
		pf_frent_remove(frag, after);
		m_freem(after->fe_m);
		uma_zfree(V_pf_frent_z, after);
	}

	/* If part of the queue gets too long, there is not way to recover. */
	if (pf_frent_insert(frag, frent, prev)) {
		DPFPRINTF(("fragment queue limit exceeded"));
		goto bad_fragment;
	}

	return (frag);

bad_fragment:
	REASON_SET(reason, PFRES_FRAG);
drop_fragment:
	uma_zfree(V_pf_frent_z, frent);
	return (NULL);
}