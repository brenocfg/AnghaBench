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
typedef  int /*<<< orphan*/  const spa_feature_t ;

/* Variables and functions */
 int /*<<< orphan*/  const SPA_FEATURE_ASYNC_DESTROY ; 
 int /*<<< orphan*/  const SPA_FEATURE_BOOKMARKS ; 
#define  SPA_FEATURE_DEVICE_REMOVAL 131 
 int /*<<< orphan*/  const SPA_FEATURE_EDONR ; 
 int /*<<< orphan*/  const SPA_FEATURE_EMBEDDED_DATA ; 
 int /*<<< orphan*/  const SPA_FEATURE_EMPTY_BPOBJ ; 
#define  SPA_FEATURE_ENABLED_TXG 130 
#define  SPA_FEATURE_EXTENSIBLE_DATASET 129 
 int /*<<< orphan*/  const SPA_FEATURE_FS_SS_LIMIT ; 
 int /*<<< orphan*/  const SPA_FEATURE_HOLE_BIRTH ; 
 int /*<<< orphan*/  const SPA_FEATURE_LARGE_BLOCKS ; 
 int /*<<< orphan*/  const SPA_FEATURE_LARGE_DNODE ; 
 int /*<<< orphan*/  const SPA_FEATURE_LZ4_COMPRESS ; 
 int /*<<< orphan*/  const SPA_FEATURE_MULTI_VDEV_CRASH_DUMP ; 
#define  SPA_FEATURE_NONE 128 
 int /*<<< orphan*/  const SPA_FEATURE_OBSOLETE_COUNTS ; 
 int /*<<< orphan*/  const SPA_FEATURE_POOL_CHECKPOINT ; 
 int /*<<< orphan*/  const SPA_FEATURE_SHA512 ; 
 int /*<<< orphan*/  const SPA_FEATURE_SKEIN ; 
 int /*<<< orphan*/  const SPA_FEATURE_SPACEMAP_HISTOGRAM ; 
 int /*<<< orphan*/  const SPA_FEATURE_SPACEMAP_V2 ; 
 int ZFEATURE_FLAG_ACTIVATE_ON_ENABLE ; 
 int ZFEATURE_FLAG_MOS ; 
 int ZFEATURE_FLAG_PER_DATASET ; 
 int ZFEATURE_FLAG_READONLY_COMPAT ; 
 int /*<<< orphan*/  zfeature_register (int /*<<< orphan*/  const,char*,char*,char*,int,int /*<<< orphan*/  const*) ; 

void
zpool_feature_init(void)
{
	zfeature_register(SPA_FEATURE_ASYNC_DESTROY,
	    "com.delphix:async_destroy", "async_destroy",
	    "Destroy filesystems asynchronously.",
	    ZFEATURE_FLAG_READONLY_COMPAT, NULL);

	zfeature_register(SPA_FEATURE_EMPTY_BPOBJ,
	    "com.delphix:empty_bpobj", "empty_bpobj",
	    "Snapshots use less space.",
	    ZFEATURE_FLAG_READONLY_COMPAT, NULL);

	zfeature_register(SPA_FEATURE_LZ4_COMPRESS,
	    "org.illumos:lz4_compress", "lz4_compress",
	    "LZ4 compression algorithm support.",
	    ZFEATURE_FLAG_ACTIVATE_ON_ENABLE, NULL);

	zfeature_register(SPA_FEATURE_MULTI_VDEV_CRASH_DUMP,
	    "com.joyent:multi_vdev_crash_dump", "multi_vdev_crash_dump",
	    "Crash dumps to multiple vdev pools.",
	    0, NULL);

	zfeature_register(SPA_FEATURE_SPACEMAP_HISTOGRAM,
	    "com.delphix:spacemap_histogram", "spacemap_histogram",
	    "Spacemaps maintain space histograms.",
	    ZFEATURE_FLAG_READONLY_COMPAT, NULL);

	zfeature_register(SPA_FEATURE_ENABLED_TXG,
	    "com.delphix:enabled_txg", "enabled_txg",
	    "Record txg at which a feature is enabled",
	    ZFEATURE_FLAG_READONLY_COMPAT, NULL);

	static spa_feature_t hole_birth_deps[] = { SPA_FEATURE_ENABLED_TXG,
	    SPA_FEATURE_NONE };
	zfeature_register(SPA_FEATURE_HOLE_BIRTH,
	    "com.delphix:hole_birth", "hole_birth",
	    "Retain hole birth txg for more precise zfs send",
	    ZFEATURE_FLAG_MOS | ZFEATURE_FLAG_ACTIVATE_ON_ENABLE,
	    hole_birth_deps);

	zfeature_register(SPA_FEATURE_EXTENSIBLE_DATASET,
	    "com.delphix:extensible_dataset", "extensible_dataset",
	    "Enhanced dataset functionality, used by other features.",
	    0, NULL);

	static const spa_feature_t bookmarks_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_BOOKMARKS,
	    "com.delphix:bookmarks", "bookmarks",
	    "\"zfs bookmark\" command",
	    ZFEATURE_FLAG_READONLY_COMPAT, bookmarks_deps);

	static const spa_feature_t filesystem_limits_deps[] = {
	    SPA_FEATURE_EXTENSIBLE_DATASET,
	    SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_FS_SS_LIMIT,
	    "com.joyent:filesystem_limits", "filesystem_limits",
	    "Filesystem and snapshot limits.",
	    ZFEATURE_FLAG_READONLY_COMPAT, filesystem_limits_deps);

	zfeature_register(SPA_FEATURE_EMBEDDED_DATA,
	    "com.delphix:embedded_data", "embedded_data",
	    "Blocks which compress very well use even less space.",
	    ZFEATURE_FLAG_MOS | ZFEATURE_FLAG_ACTIVATE_ON_ENABLE,
	    NULL);

	zfeature_register(SPA_FEATURE_POOL_CHECKPOINT,
	    "com.delphix:zpool_checkpoint", "zpool_checkpoint",
	    "Pool state can be checkpointed, allowing rewind later.",
	    ZFEATURE_FLAG_READONLY_COMPAT, NULL);

	zfeature_register(SPA_FEATURE_SPACEMAP_V2,
	    "com.delphix:spacemap_v2", "spacemap_v2",
	    "Space maps representing large segments are more efficient.",
	    ZFEATURE_FLAG_READONLY_COMPAT | ZFEATURE_FLAG_ACTIVATE_ON_ENABLE,
	    NULL);

	static const spa_feature_t large_blocks_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_LARGE_BLOCKS,
	    "org.open-zfs:large_blocks", "large_blocks",
	    "Support for blocks larger than 128KB.",
	    ZFEATURE_FLAG_PER_DATASET, large_blocks_deps);

	{
	static const spa_feature_t large_dnode_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_LARGE_DNODE,
	    "org.zfsonlinux:large_dnode", "large_dnode",
	    "Variable on-disk size of dnodes.",
	    ZFEATURE_FLAG_PER_DATASET, large_dnode_deps);
	}

	static const spa_feature_t sha512_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_SHA512,
	    "org.illumos:sha512", "sha512",
	    "SHA-512/256 hash algorithm.",
	    ZFEATURE_FLAG_PER_DATASET, sha512_deps);

	static const spa_feature_t skein_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_SKEIN,
	    "org.illumos:skein", "skein",
	    "Skein hash algorithm.",
	    ZFEATURE_FLAG_PER_DATASET, skein_deps);

#ifdef illumos
	static const spa_feature_t edonr_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_EDONR,
	    "org.illumos:edonr", "edonr",
	    "Edon-R hash algorithm.",
	    ZFEATURE_FLAG_PER_DATASET, edonr_deps);
#endif

	zfeature_register(SPA_FEATURE_DEVICE_REMOVAL,
	    "com.delphix:device_removal", "device_removal",
	    "Top-level vdevs can be removed, reducing logical pool size.",
	    ZFEATURE_FLAG_MOS, NULL);

	static const spa_feature_t obsolete_counts_deps[] = {
		SPA_FEATURE_EXTENSIBLE_DATASET,
		SPA_FEATURE_DEVICE_REMOVAL,
		SPA_FEATURE_NONE
	};
	zfeature_register(SPA_FEATURE_OBSOLETE_COUNTS,
	    "com.delphix:obsolete_counts", "obsolete_counts",
	    "Reduce memory used by removed devices when their blocks are "
	    "freed or remapped.",
	    ZFEATURE_FLAG_READONLY_COMPAT, obsolete_counts_deps);
}