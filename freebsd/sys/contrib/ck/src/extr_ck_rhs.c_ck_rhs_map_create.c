#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ck_rhs_no_entry_desc {int dummy; } ;
struct TYPE_5__ {void* descs; void* entries; } ;
struct TYPE_6__ {void* descs; TYPE_2__ no_entries; } ;
struct ck_rhs_map {int read_mostly; unsigned long size; unsigned int probe_limit; unsigned long capacity; unsigned long mask; unsigned long max_entries; int offset_mask; void* generation; int /*<<< orphan*/  probe_func; TYPE_3__ entries; int /*<<< orphan*/  n_entries; int /*<<< orphan*/  step; scalar_t__ probe_maximum; } ;
struct ck_rhs_entry_desc {int dummy; } ;
struct ck_rhs {int mode; scalar_t__ load_factor; TYPE_1__* m; } ;
struct TYPE_4__ {struct ck_rhs_map* (* malloc ) (unsigned long) ;} ;

/* Variables and functions */
 int CK_MD_CACHELINE ; 
 int CK_RHS_MODE_READ_MOSTLY ; 
 unsigned long CK_RHS_PROBE_L1 ; 
 int /*<<< orphan*/  CK_RHS_PROBE_L1_DEFAULT ; 
 int CK_RHS_PROBE_L1_SHIFT ; 
 unsigned long UINT_MAX ; 
 int /*<<< orphan*/  ck_cc_ffsl (unsigned long) ; 
 unsigned long ck_internal_max (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long ck_internal_power_2 (unsigned long) ; 
 int /*<<< orphan*/  ck_pr_fence_store () ; 
 int /*<<< orphan*/  ck_rhs_map_probe ; 
 int /*<<< orphan*/  ck_rhs_map_probe_rm ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct ck_rhs_map* stub1 (unsigned long) ; 

__attribute__((used)) static struct ck_rhs_map *
ck_rhs_map_create(struct ck_rhs *hs, unsigned long entries)
{
	struct ck_rhs_map *map;
	unsigned long size, n_entries, limit;

	n_entries = ck_internal_power_2(entries);
	if (n_entries < CK_RHS_PROBE_L1)
		n_entries = CK_RHS_PROBE_L1;

	if (hs->mode & CK_RHS_MODE_READ_MOSTLY)
		size = sizeof(struct ck_rhs_map) +
		    (sizeof(void *) * n_entries +
		     sizeof(struct ck_rhs_no_entry_desc) * n_entries +
		     2 * CK_MD_CACHELINE - 1);
	else
		size = sizeof(struct ck_rhs_map) +
		    (sizeof(struct ck_rhs_entry_desc) * n_entries +
		     CK_MD_CACHELINE - 1);
	map = hs->m->malloc(size);
	if (map == NULL)
		return NULL;
	map->read_mostly = !!(hs->mode & CK_RHS_MODE_READ_MOSTLY);

	map->size = size;
	/* We should probably use a more intelligent heuristic for default probe length. */
	limit = ck_internal_max(n_entries >> (CK_RHS_PROBE_L1_SHIFT + 2), CK_RHS_PROBE_L1_DEFAULT);
	if (limit > UINT_MAX)
		limit = UINT_MAX;

	map->probe_limit = (unsigned int)limit;
	map->probe_maximum = 0;
	map->capacity = n_entries;
	map->step = ck_cc_ffsl(n_entries);
	map->mask = n_entries - 1;
	map->n_entries = 0;

	map->max_entries = (map->capacity * (unsigned long)hs->load_factor) / 100;
	/* Align map allocation to cache line. */
	if (map->read_mostly) {
		map->entries.no_entries.entries = (void *)(((uintptr_t)&map[1] +
		    CK_MD_CACHELINE - 1) & ~(CK_MD_CACHELINE - 1));
		map->entries.no_entries.descs = (void *)(((uintptr_t)map->entries.no_entries.entries + (sizeof(void *) * n_entries) + CK_MD_CACHELINE - 1) &~ (CK_MD_CACHELINE - 1));
		memset(map->entries.no_entries.entries, 0,
		    sizeof(void *) * n_entries);
		memset(map->entries.no_entries.descs, 0,
		    sizeof(struct ck_rhs_no_entry_desc) * n_entries);
		map->offset_mask = (CK_MD_CACHELINE / sizeof(void *)) - 1;
		map->probe_func = ck_rhs_map_probe_rm;

	} else {
		map->entries.descs = (void *)(((uintptr_t)&map[1] +
		    CK_MD_CACHELINE - 1) & ~(CK_MD_CACHELINE - 1));
		memset(map->entries.descs, 0, sizeof(struct ck_rhs_entry_desc) * n_entries);
		map->offset_mask = (CK_MD_CACHELINE / sizeof(struct ck_rhs_entry_desc)) - 1;
		map->probe_func = ck_rhs_map_probe;
	}
	memset(map->generation, 0, sizeof map->generation);

	/* Commit entries purge with respect to map publication. */
	ck_pr_fence_store();
	return map;
}