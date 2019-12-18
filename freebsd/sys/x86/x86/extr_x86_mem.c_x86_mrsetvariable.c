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
struct mem_range_softc {int mr_cap; int mr_ndesc; struct mem_range_desc* mr_desc; } ;
struct mem_range_desc {int mr_flags; scalar_t__ mr_base; scalar_t__ mr_len; int /*<<< orphan*/  mr_owner; } ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOSPC ; 
 int MDF_ACTIVE ; 
 int MDF_ATTRMASK ; 
 int MDF_BUSY ; 
 int MDF_FORCE ; 
 int MDF_UNKNOWN ; 
 int MR686_FIXMTRR ; 
 int MTRR_N16K ; 
 int MTRR_N4K ; 
 int MTRR_N64K ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mrcopyflags (int,int) ; 
 scalar_t__ mroverlap (struct mem_range_desc*,struct mem_range_desc*) ; 
 scalar_t__ x86_mtrrconflict (int,int) ; 

__attribute__((used)) static int
x86_mrsetvariable(struct mem_range_softc *sc, struct mem_range_desc *mrd,
    int *arg)
{
	struct mem_range_desc *curr_md, *free_md;
	int i;

	/*
	 * Scan the currently active variable descriptors, look for
	 * one we exactly match (straight takeover) and for possible
	 * accidental overlaps.
	 *
	 * Keep track of the first empty variable descriptor in case
	 * we can't perform a takeover.
	 */
	i = (sc->mr_cap & MR686_FIXMTRR) ? MTRR_N64K + MTRR_N16K + MTRR_N4K : 0;
	curr_md = sc->mr_desc + i;
	free_md = NULL;
	for (; i < sc->mr_ndesc; i++, curr_md++) {
		if (curr_md->mr_flags & MDF_ACTIVE) {
			/* Exact match? */
			if (curr_md->mr_base == mrd->mr_base &&
			    curr_md->mr_len == mrd->mr_len) {

				/* Whoops, owned by someone. */
				if (curr_md->mr_flags & MDF_BUSY)
					return (EBUSY);

				/* Check that we aren't doing something risky */
				if (!(mrd->mr_flags & MDF_FORCE) &&
				    (curr_md->mr_flags & MDF_ATTRMASK) ==
				    MDF_UNKNOWN)
					return (EACCES);

				/* Ok, just hijack this entry. */
				free_md = curr_md;
				break;
			}

			/* Non-exact overlap? */
			if (mroverlap(curr_md, mrd)) {
				/* Between conflicting region types? */
				if (x86_mtrrconflict(curr_md->mr_flags,
				    mrd->mr_flags))
					return (EINVAL);
			}
		} else if (free_md == NULL) {
			free_md = curr_md;
		}
	}

	/* Got somewhere to put it? */
	if (free_md == NULL)
		return (ENOSPC);

	/* Set up new descriptor. */
	free_md->mr_base = mrd->mr_base;
	free_md->mr_len = mrd->mr_len;
	free_md->mr_flags = mrcopyflags(MDF_ACTIVE, mrd->mr_flags);
	bcopy(mrd->mr_owner, free_md->mr_owner, sizeof(mrd->mr_owner));
	return (0);
}