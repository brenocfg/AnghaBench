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
struct mem_range_softc {int dummy; } ;
struct mem_range_desc {int mr_flags; int /*<<< orphan*/  mr_owner; scalar_t__ mr_len; scalar_t__ mr_base; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int MDF_ATTRMASK ; 
 int MDF_FIRMWARE ; 
 int MDF_FORCE ; 
 int MDF_UNKNOWN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int mrcopyflags (int,int) ; 
 struct mem_range_desc* x86_mtrrfixsearch (struct mem_range_softc*,scalar_t__) ; 

__attribute__((used)) static int
x86_mrsetlow(struct mem_range_softc *sc, struct mem_range_desc *mrd, int *arg)
{
	struct mem_range_desc *first_md, *last_md, *curr_md;

	/* Range check. */
	if ((first_md = x86_mtrrfixsearch(sc, mrd->mr_base)) == NULL ||
	    (last_md = x86_mtrrfixsearch(sc, mrd->mr_base + mrd->mr_len - 1))
	    == NULL)
		return (EINVAL);

	/* Check that we aren't doing something risky. */
	if ((mrd->mr_flags & MDF_FORCE) == 0) {
		for (curr_md = first_md; curr_md <= last_md; curr_md++) {
			if ((curr_md->mr_flags & MDF_ATTRMASK) == MDF_UNKNOWN)
				return (EACCES);
		}
	}

	/* Set flags, clear set-by-firmware flag. */
	for (curr_md = first_md; curr_md <= last_md; curr_md++) {
		curr_md->mr_flags = mrcopyflags(curr_md->mr_flags &
		    ~MDF_FIRMWARE, mrd->mr_flags);
		bcopy(mrd->mr_owner, curr_md->mr_owner, sizeof(mrd->mr_owner));
	}

	return (0);
}