#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  window_cache_key_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_membuffer_t ;
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; int /*<<< orphan*/  uuid; TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__page_cache_key_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  pair_cache_key_t ;
struct TYPE_7__ {int fail_stop; int /*<<< orphan*/ * p2l_page_cache; int /*<<< orphan*/ * p2l_header_cache; int /*<<< orphan*/ * l2p_page_cache; int /*<<< orphan*/ * l2p_header_cache; int /*<<< orphan*/ * combined_window_cache; int /*<<< orphan*/ * txdelta_window_cache; int /*<<< orphan*/ * raw_window_cache; int /*<<< orphan*/ * properties_cache; int /*<<< orphan*/ * mergeinfo_existence_cache; int /*<<< orphan*/ * mergeinfo_cache; int /*<<< orphan*/ * fulltext_cache; int /*<<< orphan*/ * memcache; int /*<<< orphan*/ * revprop_cache; int /*<<< orphan*/ * changes_cache; int /*<<< orphan*/ * rep_header_cache; int /*<<< orphan*/ * node_revision_cache; int /*<<< orphan*/ * packed_offset_cache; int /*<<< orphan*/ * dir_cache; int /*<<< orphan*/  dag_node_cache; int /*<<< orphan*/ * rev_node_cache; int /*<<< orphan*/ * rev_root_id_cache; } ;
typedef  TYPE_2__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int APR_HASH_KEY_STRING ; 
 int /*<<< orphan*/  SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY ; 
 int /*<<< orphan*/  SVN_CACHE__MEMBUFFER_HIGH_PRIORITY ; 
 int /*<<< orphan*/  SVN_CACHE__MEMBUFFER_LOW_PRIORITY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* SVN_VA_NULL ; 
 int TRUE ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char const*,char const*,char*,...) ; 
 int /*<<< orphan*/  create_cache (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int,TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_global_cache_statistics ; 
 int /*<<< orphan*/  normalize_key_part (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_config (char const**,int*,int*,int*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/ * svn_cache__get_global_membuffer_cache () ; 
 int /*<<< orphan*/  svn_fs_fs__create_dag_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_deserialize ; 
 int /*<<< orphan*/ * svn_fs_fs__dag_serialize ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_changes ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_dir_entries ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_id ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_l2p_header ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_l2p_page ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_manifest ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_mergeinfo ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_node_revision ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_p2l_header ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_p2l_page ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_properties ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_raw_window ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_rep_header ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_revprops ; 
 int /*<<< orphan*/ * svn_fs_fs__deserialize_txdelta_window ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_changes ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_dir_entries ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_id ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_l2p_header ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_l2p_page ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_manifest ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_mergeinfo ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_node_revision ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_p2l_header ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_p2l_page ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_properties ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_raw_window ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_rep_header ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_revprops ; 
 int /*<<< orphan*/ * svn_fs_fs__serialize_txdelta_window ; 

svn_error_t *
svn_fs_fs__initialize_caches(svn_fs_t *fs,
                             apr_pool_t *pool)
{
  fs_fs_data_t *ffd = fs->fsap_data;
  const char *prefix = apr_pstrcat(pool,
                                   "fsfs:", fs->uuid,
                                   "/", normalize_key_part(fs->path, pool),
                                   ":",
                                   SVN_VA_NULL);
  svn_membuffer_t *membuffer;
  svn_boolean_t no_handler = ffd->fail_stop;
  svn_boolean_t cache_txdeltas;
  svn_boolean_t cache_fulltexts;
  svn_boolean_t cache_nodeprops;
  const char *cache_namespace;
  svn_boolean_t has_namespace;

  /* Evaluating the cache configuration. */
  SVN_ERR(read_config(&cache_namespace,
                      &cache_txdeltas,
                      &cache_fulltexts,
                      &cache_nodeprops,
                      fs,
                      pool));

  prefix = apr_pstrcat(pool, "ns:", cache_namespace, ":", prefix, SVN_VA_NULL);
  has_namespace = strlen(cache_namespace) > 0;

  membuffer = svn_cache__get_global_membuffer_cache();

  /* General rules for assigning cache priorities:
   *
   * - Data that can be reconstructed from other elements has low prio
   *   (e.g. fulltexts etc.)
   * - Index data required to find any of the other data has high prio
   *   (e.g. noderevs, L2P and P2L index pages)
   * - everything else should use default prio
   */

#ifdef SVN_DEBUG_CACHE_DUMP_STATS

  /* schedule printing the global access statistics upon pool cleanup,
   * i.e. when the repo instance gets closed / cleaned up.
   */
  if (membuffer)
    apr_pool_cleanup_register(fs->pool,
                              fs->pool,
                              dump_global_cache_statistics,
                              apr_pool_cleanup_null);
#endif

  /* Make the cache for revision roots.  For the vast majority of
   * commands, this is only going to contain a few entries (svnadmin
   * dump/verify is an exception here), so to reduce overhead let's
   * try to keep it to just one page.  I estimate each entry has about
   * 130 bytes of overhead (svn_revnum_t key, ID struct, and the cache_entry);
   * the default pool size is 8192, so about a fifty should fit comfortably.
   */
  SVN_ERR(create_cache(&(ffd->rev_root_id_cache),
                       NULL,
                       membuffer,
                       1, 50,
                       svn_fs_fs__serialize_id,
                       svn_fs_fs__deserialize_id,
                       sizeof(svn_revnum_t),
                       apr_pstrcat(pool, prefix, "RRI", SVN_VA_NULL),
                       0,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));

  /* Rough estimate: revision DAG nodes have size around 1kBytes, so
   * let's put 8 on a page. */
  SVN_ERR(create_cache(&(ffd->rev_node_cache),
                       NULL,
                       membuffer,
                       1, 8,
                       svn_fs_fs__dag_serialize,
                       svn_fs_fs__dag_deserialize,
                       APR_HASH_KEY_STRING,
                       apr_pstrcat(pool, prefix, "DAG", SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_LOW_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));

  /* 1st level DAG node cache */
  ffd->dag_node_cache = svn_fs_fs__create_dag_cache(fs->pool);

  /* Very rough estimate: 1K per directory. */
  SVN_ERR(create_cache(&(ffd->dir_cache),
                       NULL,
                       membuffer,
                       1, 8,
                       svn_fs_fs__serialize_dir_entries,
                       svn_fs_fs__deserialize_dir_entries,
                       sizeof(pair_cache_key_t),
                       apr_pstrcat(pool, prefix, "DIR", SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));

  /* 8 kBytes per entry (1000 revs / shared, one file offset per rev).
     Covering about 8 pack files gives us an "o.k." hit rate. */
  SVN_ERR(create_cache(&(ffd->packed_offset_cache),
                       NULL,
                       membuffer,
                       8, 1,
                       svn_fs_fs__serialize_manifest,
                       svn_fs_fs__deserialize_manifest,
                       sizeof(svn_revnum_t),
                       apr_pstrcat(pool, prefix, "PACK-MANIFEST",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));

  /* initialize node revision cache, if caching has been enabled */
  SVN_ERR(create_cache(&(ffd->node_revision_cache),
                       NULL,
                       membuffer,
                       2, 16, /* ~500 byte / entry; 32 entries total */
                       svn_fs_fs__serialize_node_revision,
                       svn_fs_fs__deserialize_node_revision,
                       sizeof(pair_cache_key_t),
                       apr_pstrcat(pool, prefix, "NODEREVS", SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));

  /* initialize representation header cache, if caching has been enabled */
  SVN_ERR(create_cache(&(ffd->rep_header_cache),
                       NULL,
                       membuffer,
                       1, 200, /* ~40 bytes / entry; 200 entries total */
                       svn_fs_fs__serialize_rep_header,
                       svn_fs_fs__deserialize_rep_header,
                       sizeof(pair_cache_key_t),
                       apr_pstrcat(pool, prefix, "REPHEADER", SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));

  /* initialize node change list cache, if caching has been enabled */
  SVN_ERR(create_cache(&(ffd->changes_cache),
                       NULL,
                       membuffer,
                       1, 8, /* 1k / entry; 8 entries total, rarely used */
                       svn_fs_fs__serialize_changes,
                       svn_fs_fs__deserialize_changes,
                       sizeof(pair_cache_key_t),
                       apr_pstrcat(pool, prefix, "CHANGES", SVN_VA_NULL),
                       0,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));

  /* if enabled, cache revprops */
  SVN_ERR(create_cache(&(ffd->revprop_cache),
                       NULL,
                       membuffer,
                       8, 20, /* ~400 bytes / entry, capa for ~2 packs */
                       svn_fs_fs__serialize_revprops,
                       svn_fs_fs__deserialize_revprops,
                       sizeof(pair_cache_key_t),
                       apr_pstrcat(pool, prefix, "REVPROP", SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY,
                       TRUE, /* contents is short-lived */
                       fs,
                       no_handler,
                       fs->pool, pool));

  /* if enabled, cache fulltext and other derived information */
  if (cache_fulltexts)
    {
      SVN_ERR(create_cache(&(ffd->fulltext_cache),
                           ffd->memcache,
                           membuffer,
                           0, 0, /* Do not use the inprocess cache */
                           /* Values are svn_stringbuf_t */
                           NULL, NULL,
                           sizeof(pair_cache_key_t),
                           apr_pstrcat(pool, prefix, "TEXT", SVN_VA_NULL),
                           SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY,
                           has_namespace,
                           fs,
                           no_handler,
                           fs->pool, pool));

      SVN_ERR(create_cache(&(ffd->mergeinfo_cache),
                           NULL,
                           membuffer,
                           0, 0, /* Do not use the inprocess cache */
                           svn_fs_fs__serialize_mergeinfo,
                           svn_fs_fs__deserialize_mergeinfo,
                           APR_HASH_KEY_STRING,
                           apr_pstrcat(pool, prefix, "MERGEINFO",
                                       SVN_VA_NULL),
                           0,
                           has_namespace,
                           fs,
                           no_handler,
                           fs->pool, pool));

      SVN_ERR(create_cache(&(ffd->mergeinfo_existence_cache),
                           NULL,
                           membuffer,
                           0, 0, /* Do not use the inprocess cache */
                           /* Values are svn_stringbuf_t */
                           NULL, NULL,
                           APR_HASH_KEY_STRING,
                           apr_pstrcat(pool, prefix, "HAS_MERGEINFO",
                                       SVN_VA_NULL),
                           0,
                           has_namespace,
                           fs,
                           no_handler,
                           fs->pool, pool));
    }
  else
    {
      ffd->fulltext_cache = NULL;
      ffd->mergeinfo_cache = NULL;
      ffd->mergeinfo_existence_cache = NULL;
    }

  /* if enabled, cache node properties */
  if (cache_nodeprops)
    {
      SVN_ERR(create_cache(&(ffd->properties_cache),
                           NULL,
                           membuffer,
                           0, 0, /* Do not use the inprocess cache */
                           svn_fs_fs__serialize_properties,
                           svn_fs_fs__deserialize_properties,
                           sizeof(pair_cache_key_t),
                           apr_pstrcat(pool, prefix, "PROP",
                                       SVN_VA_NULL),
                           SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY,
                           has_namespace,
                           fs,
                           no_handler,
                           fs->pool, pool));
    }
  else
    {
      ffd->properties_cache = NULL;
    }

  /* if enabled, cache text deltas and their combinations */
  if (cache_txdeltas)
    {
      SVN_ERR(create_cache(&(ffd->raw_window_cache),
                           NULL,
                           membuffer,
                           0, 0, /* Do not use the inprocess cache */
                           svn_fs_fs__serialize_raw_window,
                           svn_fs_fs__deserialize_raw_window,
                           sizeof(window_cache_key_t),
                           apr_pstrcat(pool, prefix, "RAW_WINDOW",
                                       SVN_VA_NULL),
                           SVN_CACHE__MEMBUFFER_LOW_PRIORITY,
                           has_namespace,
                           fs,
                           no_handler,
                           fs->pool, pool));

      SVN_ERR(create_cache(&(ffd->txdelta_window_cache),
                           NULL,
                           membuffer,
                           0, 0, /* Do not use the inprocess cache */
                           svn_fs_fs__serialize_txdelta_window,
                           svn_fs_fs__deserialize_txdelta_window,
                           sizeof(window_cache_key_t),
                           apr_pstrcat(pool, prefix, "TXDELTA_WINDOW",
                                       SVN_VA_NULL),
                           SVN_CACHE__MEMBUFFER_LOW_PRIORITY,
                           has_namespace,
                           fs,
                           no_handler,
                           fs->pool, pool));

      SVN_ERR(create_cache(&(ffd->combined_window_cache),
                           NULL,
                           membuffer,
                           0, 0, /* Do not use the inprocess cache */
                           /* Values are svn_stringbuf_t */
                           NULL, NULL,
                           sizeof(window_cache_key_t),
                           apr_pstrcat(pool, prefix, "COMBINED_WINDOW",
                                       SVN_VA_NULL),
                           SVN_CACHE__MEMBUFFER_LOW_PRIORITY,
                           has_namespace,
                           fs,
                           no_handler,
                           fs->pool, pool));
    }
  else
    {
      ffd->txdelta_window_cache = NULL;
      ffd->combined_window_cache = NULL;
    }

  SVN_ERR(create_cache(&(ffd->l2p_header_cache),
                       NULL,
                       membuffer,
                       8, 16, /* entry size varies but we must cover a
                                 reasonable number of rev / pack files
                                 to allow for delta chains to be walked
                                 efficiently etc. */
                       svn_fs_fs__serialize_l2p_header,
                       svn_fs_fs__deserialize_l2p_header,
                       sizeof(pair_cache_key_t),
                       apr_pstrcat(pool, prefix, "L2P_HEADER",
                                   (char *)NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));
  SVN_ERR(create_cache(&(ffd->l2p_page_cache),
                       NULL,
                       membuffer,
                       8, 16, /* entry size varies but we must cover a
                                 reasonable number of rev / pack files
                                 to allow for delta chains to be walked
                                 efficiently etc. */
                       svn_fs_fs__serialize_l2p_page,
                       svn_fs_fs__deserialize_l2p_page,
                       sizeof(svn_fs_fs__page_cache_key_t),
                       apr_pstrcat(pool, prefix, "L2P_PAGE",
                                   (char *)NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));
  SVN_ERR(create_cache(&(ffd->p2l_header_cache),
                       NULL,
                       membuffer,
                       4, 1, /* Large entries. Rarely used. */
                       svn_fs_fs__serialize_p2l_header,
                       svn_fs_fs__deserialize_p2l_header,
                       sizeof(pair_cache_key_t),
                       apr_pstrcat(pool, prefix, "P2L_HEADER",
                                   (char *)NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));
  SVN_ERR(create_cache(&(ffd->p2l_page_cache),
                       NULL,
                       membuffer,
                       4, 1, /* Variably sized entries. Rarely used. */
                       svn_fs_fs__serialize_p2l_page,
                       svn_fs_fs__deserialize_p2l_page,
                       sizeof(svn_fs_fs__page_cache_key_t),
                       apr_pstrcat(pool, prefix, "P2L_PAGE",
                                   (char *)NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler,
                       fs->pool, pool));

  return SVN_NO_ERROR;
}