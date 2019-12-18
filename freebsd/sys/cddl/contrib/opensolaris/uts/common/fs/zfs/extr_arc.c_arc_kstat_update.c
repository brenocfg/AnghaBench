#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* ks_data; } ;
typedef  TYPE_1__ kstat_t ;
struct TYPE_5__ {int /*<<< orphan*/  arcstat_mfu_ghost_evictable_metadata; int /*<<< orphan*/  arcstat_mfu_ghost_evictable_data; int /*<<< orphan*/  arcstat_mfu_ghost_size; int /*<<< orphan*/  arcstat_mfu_evictable_metadata; int /*<<< orphan*/  arcstat_mfu_evictable_data; int /*<<< orphan*/  arcstat_mfu_size; int /*<<< orphan*/  arcstat_mru_ghost_evictable_metadata; int /*<<< orphan*/  arcstat_mru_ghost_evictable_data; int /*<<< orphan*/  arcstat_mru_ghost_size; int /*<<< orphan*/  arcstat_mru_evictable_metadata; int /*<<< orphan*/  arcstat_mru_evictable_data; int /*<<< orphan*/  arcstat_mru_size; int /*<<< orphan*/  arcstat_anon_evictable_metadata; int /*<<< orphan*/  arcstat_anon_evictable_data; int /*<<< orphan*/  arcstat_anon_size; } ;
typedef  TYPE_2__ arc_stats_t ;
typedef  scalar_t__ ARCSTAT ;

/* Variables and functions */
 int EACCES ; 
 int KSTAT_WRITE ; 
 scalar_t__ aggsum_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_anon ; 
 int /*<<< orphan*/  arc_kstat_update_state (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arc_meta_used ; 
 int /*<<< orphan*/  arc_mfu ; 
 int /*<<< orphan*/  arc_mfu_ghost ; 
 int /*<<< orphan*/  arc_mru ; 
 int /*<<< orphan*/  arc_mru_ghost ; 
 int /*<<< orphan*/  arc_size ; 
 int /*<<< orphan*/  astat_bonus_size ; 
 int /*<<< orphan*/  astat_data_size ; 
 int /*<<< orphan*/  astat_dbuf_size ; 
 int /*<<< orphan*/  astat_dnode_size ; 
 int /*<<< orphan*/  astat_hdr_size ; 
 int /*<<< orphan*/  astat_l2_hdr_size ; 
 int /*<<< orphan*/  astat_metadata_size ; 

__attribute__((used)) static int
arc_kstat_update(kstat_t *ksp, int rw)
{
	arc_stats_t *as = ksp->ks_data;

	if (rw == KSTAT_WRITE) {
		return (EACCES);
	} else {
		arc_kstat_update_state(arc_anon,
		    &as->arcstat_anon_size,
		    &as->arcstat_anon_evictable_data,
		    &as->arcstat_anon_evictable_metadata);
		arc_kstat_update_state(arc_mru,
		    &as->arcstat_mru_size,
		    &as->arcstat_mru_evictable_data,
		    &as->arcstat_mru_evictable_metadata);
		arc_kstat_update_state(arc_mru_ghost,
		    &as->arcstat_mru_ghost_size,
		    &as->arcstat_mru_ghost_evictable_data,
		    &as->arcstat_mru_ghost_evictable_metadata);
		arc_kstat_update_state(arc_mfu,
		    &as->arcstat_mfu_size,
		    &as->arcstat_mfu_evictable_data,
		    &as->arcstat_mfu_evictable_metadata);
		arc_kstat_update_state(arc_mfu_ghost,
		    &as->arcstat_mfu_ghost_size,
		    &as->arcstat_mfu_ghost_evictable_data,
		    &as->arcstat_mfu_ghost_evictable_metadata);

		ARCSTAT(arcstat_size) = aggsum_value(&arc_size);
		ARCSTAT(arcstat_meta_used) = aggsum_value(&arc_meta_used);
		ARCSTAT(arcstat_data_size) = aggsum_value(&astat_data_size);
		ARCSTAT(arcstat_metadata_size) =
		    aggsum_value(&astat_metadata_size);
		ARCSTAT(arcstat_hdr_size) = aggsum_value(&astat_hdr_size);
		ARCSTAT(arcstat_bonus_size) = aggsum_value(&astat_bonus_size);
		ARCSTAT(arcstat_dnode_size) = aggsum_value(&astat_dnode_size);
		ARCSTAT(arcstat_dbuf_size) = aggsum_value(&astat_dbuf_size);
#if defined(__FreeBSD__) && defined(COMPAT_FREEBSD11)
		ARCSTAT(arcstat_other_size) = aggsum_value(&astat_bonus_size) +
		    aggsum_value(&astat_dnode_size) +
		    aggsum_value(&astat_dbuf_size);
#endif
		ARCSTAT(arcstat_l2_hdr_size) = aggsum_value(&astat_l2_hdr_size);
	}

	return (0);
}