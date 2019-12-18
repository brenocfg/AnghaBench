#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vs ;
struct TYPE_10__ {int vs_alloc; int vs_aux; } ;
struct TYPE_13__ {int vic_mapping_object; int vic_births_object; int vic_prev_indirect_vdev; } ;
struct TYPE_12__ {int vdev_id; int vdev_guid; char const* vdev_path; char const* vdev_devid; char const* vdev_physpath; char const* vdev_fru; int vdev_nparity; unsigned long long vdev_wholedisk; int vdev_ms_array; int vdev_ms_shift; int vdev_ashift; int vdev_asize; int vdev_islog; int vdev_removing; int vdev_crtxg; int vdev_leaf_zap; int vdev_top_zap; int vdev_children; int vdev_resilver_txg; long long vdev_orig_guid; scalar_t__ vdev_splitting; TYPE_2__ vdev_stat; scalar_t__ vdev_ishole; scalar_t__ vdev_unspare; scalar_t__ vdev_removed; scalar_t__ vdev_degraded; scalar_t__ vdev_faulted; int /*<<< orphan*/  vdev_tmpoffline; scalar_t__ vdev_offline; struct TYPE_12__** vdev_child; TYPE_3__* vdev_ops; TYPE_1__* vdev_mg; int /*<<< orphan*/  vdev_indirect_rwlock; int /*<<< orphan*/ * vdev_indirect_mapping; int /*<<< orphan*/ * vdev_indirect_births; struct TYPE_12__* vdev_top; int /*<<< orphan*/ * vdev_dtl_sm; scalar_t__ vdev_isspare; scalar_t__ vdev_not_present; TYPE_5__ vdev_indirect_config; } ;
typedef  TYPE_4__ vdev_t ;
typedef  int /*<<< orphan*/  vdev_stat_t ;
typedef  int /*<<< orphan*/  vdev_indirect_mapping_t ;
typedef  int /*<<< orphan*/  vdev_indirect_mapping_entry_phys_t ;
typedef  TYPE_5__ vdev_indirect_config_t ;
typedef  int vdev_config_flag_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_11__ {char const* vdev_op_type; int vdev_op_leaf; } ;
struct TYPE_9__ {scalar_t__ mg_fragmentation; int* mg_histogram; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int B_TRUE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int RANGE_TREE_HISTOGRAM_SIZE ; 
 int /*<<< orphan*/  RW_READER ; 
 scalar_t__ SPA_VERSION_RAIDZ2 ; 
 scalar_t__ SPA_VERSION_RAIDZ3 ; 
 int UINT64_MAX ; 
#define  VDEV_AUX_ERR_EXCEEDED 129 
#define  VDEV_AUX_EXTERNAL 128 
 int VDEV_CONFIG_L2CACHE ; 
 int VDEV_CONFIG_MISSING ; 
 int VDEV_CONFIG_MOS ; 
 int VDEV_CONFIG_REMOVING ; 
 int VDEV_CONFIG_SPARE ; 
 int /*<<< orphan*/  VDEV_TYPE_RAIDZ ; 
 scalar_t__ ZFS_FRAG_INVALID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ASHIFT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ASIZE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_AUX_STATE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CREATE_TXG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_DEGRADED ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_DEVID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_DTL ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_FAULTED ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_FRU ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_INDIRECT_BIRTHS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_INDIRECT_OBJECT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_INDIRECT_SIZE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_HOLE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_LOG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_SPARE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_METASLAB_ARRAY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_METASLAB_SHIFT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_NOT_PRESENT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_NPARITY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_OFFLINE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ORIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PHYS_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PREV_INDIRECT_VDEV ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_REMOVED ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_REMOVING ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_RESILVER_TXG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_UNSPARE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_LEAF_ZAP ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_STATS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TOP_ZAP ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_WHOLE_DISK ; 
 int /*<<< orphan*/  fnvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fnvlist_add_uint64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/ ** kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  root_vdev_actions_getprogress (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_version (int /*<<< orphan*/ *) ; 
 int space_map_object (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_get_stats (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int vdev_indirect_mapping_size (int /*<<< orphan*/ *) ; 
 int vdev_removal_max_span ; 
 int zfs_remove_max_segment ; 

nvlist_t *
vdev_config_generate(spa_t *spa, vdev_t *vd, boolean_t getstats,
    vdev_config_flag_t flags)
{
	nvlist_t *nv = NULL;
	vdev_indirect_config_t *vic = &vd->vdev_indirect_config;

	nv = fnvlist_alloc();

	fnvlist_add_string(nv, ZPOOL_CONFIG_TYPE, vd->vdev_ops->vdev_op_type);
	if (!(flags & (VDEV_CONFIG_SPARE | VDEV_CONFIG_L2CACHE)))
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_ID, vd->vdev_id);
	fnvlist_add_uint64(nv, ZPOOL_CONFIG_GUID, vd->vdev_guid);

	if (vd->vdev_path != NULL)
		fnvlist_add_string(nv, ZPOOL_CONFIG_PATH, vd->vdev_path);

	if (vd->vdev_devid != NULL)
		fnvlist_add_string(nv, ZPOOL_CONFIG_DEVID, vd->vdev_devid);

	if (vd->vdev_physpath != NULL)
		fnvlist_add_string(nv, ZPOOL_CONFIG_PHYS_PATH,
		    vd->vdev_physpath);

	if (vd->vdev_fru != NULL)
		fnvlist_add_string(nv, ZPOOL_CONFIG_FRU, vd->vdev_fru);

	if (vd->vdev_nparity != 0) {
		ASSERT(strcmp(vd->vdev_ops->vdev_op_type,
		    VDEV_TYPE_RAIDZ) == 0);

		/*
		 * Make sure someone hasn't managed to sneak a fancy new vdev
		 * into a crufty old storage pool.
		 */
		ASSERT(vd->vdev_nparity == 1 ||
		    (vd->vdev_nparity <= 2 &&
		    spa_version(spa) >= SPA_VERSION_RAIDZ2) ||
		    (vd->vdev_nparity <= 3 &&
		    spa_version(spa) >= SPA_VERSION_RAIDZ3));

		/*
		 * Note that we'll add the nparity tag even on storage pools
		 * that only support a single parity device -- older software
		 * will just ignore it.
		 */
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_NPARITY, vd->vdev_nparity);
	}

	if (vd->vdev_wholedisk != -1ULL)
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_WHOLE_DISK,
		    vd->vdev_wholedisk);

	if (vd->vdev_not_present && !(flags & VDEV_CONFIG_MISSING))
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_NOT_PRESENT, 1);

	if (vd->vdev_isspare)
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_IS_SPARE, 1);

	if (!(flags & (VDEV_CONFIG_SPARE | VDEV_CONFIG_L2CACHE)) &&
	    vd == vd->vdev_top) {
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_METASLAB_ARRAY,
		    vd->vdev_ms_array);
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_METASLAB_SHIFT,
		    vd->vdev_ms_shift);
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_ASHIFT, vd->vdev_ashift);
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_ASIZE,
		    vd->vdev_asize);
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_IS_LOG, vd->vdev_islog);
		if (vd->vdev_removing) {
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_REMOVING,
			    vd->vdev_removing);
		}
	}

	if (vd->vdev_dtl_sm != NULL) {
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_DTL,
		    space_map_object(vd->vdev_dtl_sm));
	}

	if (vic->vic_mapping_object != 0) {
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_INDIRECT_OBJECT,
		    vic->vic_mapping_object);
	}

	if (vic->vic_births_object != 0) {
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_INDIRECT_BIRTHS,
		    vic->vic_births_object);
	}

	if (vic->vic_prev_indirect_vdev != UINT64_MAX) {
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_PREV_INDIRECT_VDEV,
		    vic->vic_prev_indirect_vdev);
	}

	if (vd->vdev_crtxg)
		fnvlist_add_uint64(nv, ZPOOL_CONFIG_CREATE_TXG, vd->vdev_crtxg);

	if (flags & VDEV_CONFIG_MOS) {
		if (vd->vdev_leaf_zap != 0) {
			ASSERT(vd->vdev_ops->vdev_op_leaf);
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_VDEV_LEAF_ZAP,
			    vd->vdev_leaf_zap);
		}

		if (vd->vdev_top_zap != 0) {
			ASSERT(vd == vd->vdev_top);
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_VDEV_TOP_ZAP,
			    vd->vdev_top_zap);
		}
	}

	if (getstats) {
		vdev_stat_t vs;

		vdev_get_stats(vd, &vs);
		fnvlist_add_uint64_array(nv, ZPOOL_CONFIG_VDEV_STATS,
		    (uint64_t *)&vs, sizeof (vs) / sizeof (uint64_t));

		root_vdev_actions_getprogress(vd, nv);

		/*
		 * Note: this can be called from open context
		 * (spa_get_stats()), so we need the rwlock to prevent
		 * the mapping from being changed by condensing.
		 */
		rw_enter(&vd->vdev_indirect_rwlock, RW_READER);
		if (vd->vdev_indirect_mapping != NULL) {
			ASSERT(vd->vdev_indirect_births != NULL);
			vdev_indirect_mapping_t *vim =
			    vd->vdev_indirect_mapping;
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_INDIRECT_SIZE,
			    vdev_indirect_mapping_size(vim));
		}
		rw_exit(&vd->vdev_indirect_rwlock);
		if (vd->vdev_mg != NULL &&
		    vd->vdev_mg->mg_fragmentation != ZFS_FRAG_INVALID) {
			/*
			 * Compute approximately how much memory would be used
			 * for the indirect mapping if this device were to
			 * be removed.
			 *
			 * Note: If the frag metric is invalid, then not
			 * enough metaslabs have been converted to have
			 * histograms.
			 */
			uint64_t seg_count = 0;
			uint64_t to_alloc = vd->vdev_stat.vs_alloc;

			/*
			 * There are the same number of allocated segments
			 * as free segments, so we will have at least one
			 * entry per free segment.  However, small free
			 * segments (smaller than vdev_removal_max_span)
			 * will be combined with adjacent allocated segments
			 * as a single mapping.
			 */
			for (int i = 0; i < RANGE_TREE_HISTOGRAM_SIZE; i++) {
				if (1ULL << (i + 1) < vdev_removal_max_span) {
					to_alloc +=
					    vd->vdev_mg->mg_histogram[i] <<
					    i + 1;
				} else {
					seg_count +=
					    vd->vdev_mg->mg_histogram[i];
				}
			}

			/*
			 * The maximum length of a mapping is
			 * zfs_remove_max_segment, so we need at least one entry
			 * per zfs_remove_max_segment of allocated data.
			 */
			seg_count += to_alloc / zfs_remove_max_segment;

			fnvlist_add_uint64(nv, ZPOOL_CONFIG_INDIRECT_SIZE,
			    seg_count *
			    sizeof (vdev_indirect_mapping_entry_phys_t));
		}
	}

	if (!vd->vdev_ops->vdev_op_leaf) {
		nvlist_t **child;
		int c, idx;

		ASSERT(!vd->vdev_ishole);

		child = kmem_alloc(vd->vdev_children * sizeof (nvlist_t *),
		    KM_SLEEP);

		for (c = 0, idx = 0; c < vd->vdev_children; c++) {
			vdev_t *cvd = vd->vdev_child[c];

			/*
			 * If we're generating an nvlist of removing
			 * vdevs then skip over any device which is
			 * not being removed.
			 */
			if ((flags & VDEV_CONFIG_REMOVING) &&
			    !cvd->vdev_removing)
				continue;

			child[idx++] = vdev_config_generate(spa, cvd,
			    getstats, flags);
		}

		if (idx) {
			fnvlist_add_nvlist_array(nv, ZPOOL_CONFIG_CHILDREN,
			    child, idx);
		}

		for (c = 0; c < idx; c++)
			nvlist_free(child[c]);

		kmem_free(child, vd->vdev_children * sizeof (nvlist_t *));

	} else {
		const char *aux = NULL;

		if (vd->vdev_offline && !vd->vdev_tmpoffline)
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_OFFLINE, B_TRUE);
		if (vd->vdev_resilver_txg != 0)
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_RESILVER_TXG,
			    vd->vdev_resilver_txg);
		if (vd->vdev_faulted)
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_FAULTED, B_TRUE);
		if (vd->vdev_degraded)
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_DEGRADED, B_TRUE);
		if (vd->vdev_removed)
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_REMOVED, B_TRUE);
		if (vd->vdev_unspare)
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_UNSPARE, B_TRUE);
		if (vd->vdev_ishole)
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_IS_HOLE, B_TRUE);

		switch (vd->vdev_stat.vs_aux) {
		case VDEV_AUX_ERR_EXCEEDED:
			aux = "err_exceeded";
			break;

		case VDEV_AUX_EXTERNAL:
			aux = "external";
			break;
		}

		if (aux != NULL)
			fnvlist_add_string(nv, ZPOOL_CONFIG_AUX_STATE, aux);

		if (vd->vdev_splitting && vd->vdev_orig_guid != 0LL) {
			fnvlist_add_uint64(nv, ZPOOL_CONFIG_ORIG_GUID,
			    vd->vdev_orig_guid);
		}
	}

	return (nv);
}