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
struct ck_rhs_map {unsigned long probe_maximum; int /*<<< orphan*/ * generation; } ;
struct ck_rhs_entry_desc {scalar_t__ wanted; unsigned int probes; unsigned long probe_bound; } ;
struct ck_rhs {struct ck_rhs_map* map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_RHS_EMPTY ; 
 unsigned long CK_RHS_G_MASK ; 
 scalar_t__ CK_RHS_MAX_WANTED ; 
 int /*<<< orphan*/  CK_RHS_STORE (unsigned long*,int) ; 
 unsigned long CK_RHS_WORD_MAX ; 
 int /*<<< orphan*/  ck_pr_fence_atomic_store () ; 
 int /*<<< orphan*/  ck_pr_inc_uint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ck_pr_store_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ck_rhs_entry_desc* ck_rhs_desc (struct ck_rhs_map*,unsigned long) ; 
 int /*<<< orphan*/  ck_rhs_entry (struct ck_rhs_map*,unsigned long) ; 
 int /*<<< orphan*/  ck_rhs_entry_addr (struct ck_rhs_map*,long) ; 
 scalar_t__ ck_rhs_get_first_offset (struct ck_rhs_map*,unsigned long,unsigned int) ; 
 unsigned long ck_rhs_map_probe_next (struct ck_rhs_map*,unsigned long,unsigned int) ; 
 unsigned long* ck_rhs_probe_bound_addr (struct ck_rhs_map*,unsigned long) ; 
 unsigned long ck_rhs_remove_wanted (struct ck_rhs*,unsigned long,long) ; 

__attribute__((used)) static void
ck_rhs_do_backward_shift_delete(struct ck_rhs *hs, long slot)
{
	struct ck_rhs_map *map = hs->map;
	struct ck_rhs_entry_desc *desc, *new_desc = NULL;
	unsigned long h;

	desc = ck_rhs_desc(map, slot);
	h = ck_rhs_remove_wanted(hs, slot, -1);
	while (desc->wanted > 0) {
		unsigned long offset = 0, tmp_offset;
		unsigned long wanted_probes = 1;
		unsigned int probe = 0;
		unsigned int max_probes;

		/* Find a successor */
		while (wanted_probes < map->probe_maximum) {
			probe = wanted_probes;
			offset = ck_rhs_map_probe_next(map, slot, probe);
			while (probe < map->probe_maximum) {
				new_desc = ck_rhs_desc(map, offset);
				if (new_desc->probes == probe + 1)
					break;
				probe++;
				offset = ck_rhs_map_probe_next(map, offset,
				    probe);
			}
			if (probe < map->probe_maximum)
				break;
			wanted_probes++;
		}
		if (!(wanted_probes < map->probe_maximum)) {
			desc->wanted = 0;
			break;
		}
		desc->probes = wanted_probes;
		h = ck_rhs_remove_wanted(hs, offset, slot);
		ck_pr_store_ptr(ck_rhs_entry_addr(map, slot),
		    ck_rhs_entry(map, offset));
		ck_pr_inc_uint(&map->generation[h & CK_RHS_G_MASK]);
		ck_pr_fence_atomic_store();
		if (wanted_probes < CK_RHS_WORD_MAX) {
			struct ck_rhs_entry_desc *hdesc = ck_rhs_desc(map, h);
			if (hdesc->wanted == 1)
				CK_RHS_STORE(&hdesc->probe_bound,
				    wanted_probes);
			else if (hdesc->probe_bound == CK_RHS_WORD_MAX ||
			    hdesc->probe_bound == new_desc->probes) {
				probe++;
				if (hdesc->probe_bound == CK_RHS_WORD_MAX)
					max_probes = map->probe_maximum;
				else {
					max_probes = hdesc->probe_bound;
					max_probes--;
				}
				tmp_offset = ck_rhs_map_probe_next(map, offset,
				    probe);
				while (probe < max_probes) {
					if (h == (unsigned long)ck_rhs_get_first_offset(map, tmp_offset, probe))
						break;
					probe++;
					tmp_offset = ck_rhs_map_probe_next(map, tmp_offset, probe);
				}
				if (probe == max_probes)
					CK_RHS_STORE(&hdesc->probe_bound,
					    wanted_probes);
			}
		}
		if (desc->wanted < CK_RHS_MAX_WANTED)
			desc->wanted--;
		slot = offset;
		desc = new_desc;
	}
	ck_pr_store_ptr(ck_rhs_entry_addr(map, slot), CK_RHS_EMPTY);
	if ((desc->probes - 1) < CK_RHS_WORD_MAX)
		CK_RHS_STORE(ck_rhs_probe_bound_addr(map, h),
		    desc->probes - 1);
	desc->probes = 0;
}