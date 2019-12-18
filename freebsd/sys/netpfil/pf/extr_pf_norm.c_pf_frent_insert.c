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
struct pf_frent {scalar_t__ fe_off; scalar_t__ fe_len; } ;
struct pf_fragment {int* fr_entries; int /*<<< orphan*/  fr_holes; struct pf_frent** fr_firstoff; int /*<<< orphan*/  fr_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PF_FRAG_ENTRY_LIMIT ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct pf_frent*,struct pf_frent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct pf_frent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fr_next ; 
 scalar_t__ pf_frent_holes (struct pf_frent*) ; 
 int pf_frent_index (struct pf_frent*) ; 

__attribute__((used)) static int
pf_frent_insert(struct pf_fragment *frag, struct pf_frent *frent,
    struct pf_frent *prev)
{
	int index;

	CTASSERT(PF_FRAG_ENTRY_LIMIT <= 0xff);

	/*
	 * A packet has at most 65536 octets.  With 16 entry points, each one
	 * spawns 4096 octets.  We limit these to 64 fragments each, which
	 * means on average every fragment must have at least 64 octets.
	 */
	index = pf_frent_index(frent);
	if (frag->fr_entries[index] >= PF_FRAG_ENTRY_LIMIT)
		return ENOBUFS;
	frag->fr_entries[index]++;

	if (prev == NULL) {
		TAILQ_INSERT_HEAD(&frag->fr_queue, frent, fr_next);
	} else {
		KASSERT(prev->fe_off + prev->fe_len <= frent->fe_off,
		    ("overlapping fragment"));
		TAILQ_INSERT_AFTER(&frag->fr_queue, prev, frent, fr_next);
	}

	if (frag->fr_firstoff[index] == NULL) {
		KASSERT(prev == NULL || pf_frent_index(prev) < index,
		    ("prev == NULL || pf_frent_index(pref) < index"));
		frag->fr_firstoff[index] = frent;
	} else {
		if (frent->fe_off < frag->fr_firstoff[index]->fe_off) {
			KASSERT(prev == NULL || pf_frent_index(prev) < index,
			    ("prev == NULL || pf_frent_index(pref) < index"));
			frag->fr_firstoff[index] = frent;
		} else {
			KASSERT(prev != NULL, ("prev != NULL"));
			KASSERT(pf_frent_index(prev) == index,
			    ("pf_frent_index(prev) == index"));
		}
	}

	frag->fr_holes += pf_frent_holes(frent);

	return 0;
}