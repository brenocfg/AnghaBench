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
struct drmem_lmb {int flags; int aa_index; } ;
struct assoc_arrays {int array_sz; int n_arrays; int /*<<< orphan*/ * arrays; } ;

/* Variables and functions */
 int DRCONF_MEM_AI_INVALID ; 
 int MAX_NUMNODES ; 
 int NUMA_NO_NODE ; 
 int /*<<< orphan*/  initialize_distance_lookup_table (int,int /*<<< orphan*/ *) ; 
 int min_common_depth ; 
 int /*<<< orphan*/  numa_enabled ; 
 int of_get_assoc_arrays (struct assoc_arrays*) ; 
 int of_read_number (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int of_drconf_to_nid_single(struct drmem_lmb *lmb)
{
	struct assoc_arrays aa = { .arrays = NULL };
	int default_nid = NUMA_NO_NODE;
	int nid = default_nid;
	int rc, index;

	if ((min_common_depth < 0) || !numa_enabled)
		return default_nid;

	rc = of_get_assoc_arrays(&aa);
	if (rc)
		return default_nid;

	if (min_common_depth <= aa.array_sz &&
	    !(lmb->flags & DRCONF_MEM_AI_INVALID) && lmb->aa_index < aa.n_arrays) {
		index = lmb->aa_index * aa.array_sz + min_common_depth - 1;
		nid = of_read_number(&aa.arrays[index], 1);

		if (nid == 0xffff || nid >= MAX_NUMNODES)
			nid = default_nid;

		if (nid > 0) {
			index = lmb->aa_index * aa.array_sz;
			initialize_distance_lookup_table(nid,
							&aa.arrays[index]);
		}
	}

	return nid;
}