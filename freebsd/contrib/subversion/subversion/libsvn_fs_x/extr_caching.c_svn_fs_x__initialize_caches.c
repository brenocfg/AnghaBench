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
typedef  int /*<<< orphan*/  svn_membuffer_t ;
typedef  int /*<<< orphan*/  svn_fs_x__window_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_x__representation_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_x__pair_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_x__page_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
struct TYPE_6__ {int fail_stop; int /*<<< orphan*/  p2l_page_cache; int /*<<< orphan*/  p2l_header_cache; int /*<<< orphan*/  l2p_page_cache; int /*<<< orphan*/  l2p_header_cache; int /*<<< orphan*/  reps_container_cache; int /*<<< orphan*/  changes_container_cache; int /*<<< orphan*/  noderevs_container_cache; int /*<<< orphan*/  combined_window_cache; int /*<<< orphan*/  txdelta_window_cache; int /*<<< orphan*/  revprop_cache; int /*<<< orphan*/  properties_cache; int /*<<< orphan*/ * memcache; int /*<<< orphan*/  fulltext_cache; int /*<<< orphan*/  changes_cache; int /*<<< orphan*/  rep_header_cache; int /*<<< orphan*/  node_revision_cache; int /*<<< orphan*/  dir_cache; int /*<<< orphan*/  dag_node_cache; int /*<<< orphan*/  instance_id; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_7__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; int /*<<< orphan*/  uuid; TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY ; 
 int /*<<< orphan*/  SVN_CACHE__MEMBUFFER_HIGH_PRIORITY ; 
 int /*<<< orphan*/  SVN_CACHE__MEMBUFFER_LOW_PRIORITY ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char const*,char const*,char*,...) ; 
 int /*<<< orphan*/  create_cache (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int,TYPE_2__*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_global_cache_statistics ; 
 int /*<<< orphan*/  normalize_key_part (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_config (char const**,int*,int*,int*,int*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/ * svn_cache__get_global_membuffer_cache () ; 
 int /*<<< orphan*/  svn_fs_x__create_dag_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_changes ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_changes_container ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_dir_entries ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_l2p_header ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_l2p_page ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_node_revision ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_noderevs_container ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_p2l_header ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_p2l_page ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_properties ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_rep_header ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_reps_container ; 
 int /*<<< orphan*/ * svn_fs_x__deserialize_txdelta_window ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_changes ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_changes_container ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_dir_entries ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_l2p_header ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_l2p_page ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_node_revision ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_noderevs_container ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_p2l_header ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_p2l_page ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_properties ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_rep_header ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_reps_container ; 
 int /*<<< orphan*/ * svn_fs_x__serialize_txdelta_window ; 

svn_error_t *
svn_fs_x__initialize_caches(svn_fs_t *fs,
                            apr_pool_t *scratch_pool)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;
  const char *prefix = apr_pstrcat(scratch_pool,
                                   "fsx:", fs->uuid,
                                   "--", ffd->instance_id,
                                   "/", normalize_key_part(fs->path,
                                                           scratch_pool),
                                   ":",
                                   SVN_VA_NULL);
  svn_membuffer_t *membuffer;
  svn_boolean_t no_handler = ffd->fail_stop;
  svn_boolean_t cache_txdeltas;
  svn_boolean_t cache_fulltexts;
  svn_boolean_t cache_revprops;
  svn_boolean_t cache_nodeprops;
  const char *cache_namespace;
  svn_boolean_t has_namespace;

  /* Evaluating the cache configuration. */
  SVN_ERR(read_config(&cache_namespace,
                      &cache_txdeltas,
                      &cache_fulltexts,
                      &cache_revprops,
                      &cache_nodeprops,
                      fs,
                      scratch_pool));

  prefix = apr_pstrcat(scratch_pool, "ns:", cache_namespace, ":", prefix,
                       SVN_VA_NULL);
  has_namespace = strlen(cache_namespace) > 0;

  membuffer = svn_cache__get_global_membuffer_cache();

  /* General rules for assigning cache priorities:
   *
   * - Data that can be reconstructed from other elements has low prio
   *   (e.g. fulltexts etc.)
   * - Index data required to find any of the other data has high prio
   *   (e.g. noderevs, L2P and P2L index pages)
   * - everthing else should use default prio
   */

#ifdef SVN_DEBUG_CACHE_DUMP_STATS

  /* schedule printing the global access statistics upon pool cleanup,
   * i.e. end of FSX session.
   */
  if (membuffer)
    apr_pool_cleanup_register(fs->pool,
                              fs->pool,
                              dump_global_cache_statistics,
                              apr_pool_cleanup_null);
#endif

  /* 1st level DAG node cache */
  ffd->dag_node_cache = svn_fs_x__create_dag_cache(fs->pool);

  /* Very rough estimate: 1K per directory. */
  SVN_ERR(create_cache(&(ffd->dir_cache),
                       NULL,
                       membuffer,
                       1024, 8,
                       svn_fs_x__serialize_dir_entries,
                       svn_fs_x__deserialize_dir_entries,
                       sizeof(svn_fs_x__id_t),
                       apr_pstrcat(scratch_pool, prefix, "DIR", SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));

  /* initialize node revision cache, if caching has been enabled */
  SVN_ERR(create_cache(&(ffd->node_revision_cache),
                       NULL,
                       membuffer,
                       32, 32, /* ~200 byte / entry; 1k entries total */
                       svn_fs_x__serialize_node_revision,
                       svn_fs_x__deserialize_node_revision,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "NODEREVS",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));

  /* initialize representation header cache, if caching has been enabled */
  SVN_ERR(create_cache(&(ffd->rep_header_cache),
                       NULL,
                       membuffer,
                       1, 1000, /* ~8 bytes / entry; 1k entries total */
                       svn_fs_x__serialize_rep_header,
                       svn_fs_x__deserialize_rep_header,
                       sizeof(svn_fs_x__representation_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "REPHEADER",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));

  /* initialize node change list cache, if caching has been enabled */
  SVN_ERR(create_cache(&(ffd->changes_cache),
                       NULL,
                       membuffer,
                       1, 8, /* 1k / entry; 8 entries total, rarely used */
                       svn_fs_x__serialize_changes,
                       svn_fs_x__deserialize_changes,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "CHANGES",
                                   SVN_VA_NULL),
                       0,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));

  /* if enabled, cache fulltext and other derived information */
  SVN_ERR(create_cache(&(ffd->fulltext_cache),
                       ffd->memcache,
                       membuffer,
                       0, 0, /* Do not use inprocess cache */
                       /* Values are svn_stringbuf_t */
                       NULL, NULL,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "TEXT",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, !cache_fulltexts,
                       fs->pool, scratch_pool));

  SVN_ERR(create_cache(&(ffd->properties_cache),
                       NULL,
                       membuffer,
                       0, 0, /* Do not use inprocess cache */
                       svn_fs_x__serialize_properties,
                       svn_fs_x__deserialize_properties,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "PROP",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, !cache_nodeprops,
                       fs->pool, scratch_pool));

  /* if enabled, cache revprops */
  SVN_ERR(create_cache(&(ffd->revprop_cache),
                       NULL,
                       membuffer,
                       0, 0, /* Do not use inprocess cache */
                       svn_fs_x__serialize_properties,
                       svn_fs_x__deserialize_properties,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "REVPROP",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_DEFAULT_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, !cache_revprops,
                       fs->pool, scratch_pool));

  /* if enabled, cache text deltas and their combinations */
  SVN_ERR(create_cache(&(ffd->txdelta_window_cache),
                       NULL,
                       membuffer,
                       0, 0, /* Do not use inprocess cache */
                       svn_fs_x__serialize_txdelta_window,
                       svn_fs_x__deserialize_txdelta_window,
                       sizeof(svn_fs_x__window_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "TXDELTA_WINDOW",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_LOW_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, !cache_txdeltas,
                       fs->pool, scratch_pool));

  SVN_ERR(create_cache(&(ffd->combined_window_cache),
                       NULL,
                       membuffer,
                       0, 0, /* Do not use inprocess cache */
                       /* Values are svn_stringbuf_t */
                       NULL, NULL,
                       sizeof(svn_fs_x__window_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "COMBINED_WINDOW",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_LOW_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, !cache_txdeltas,
                       fs->pool, scratch_pool));

  /* Caches for our various container types. */
  SVN_ERR(create_cache(&(ffd->noderevs_container_cache),
                       NULL,
                       membuffer,
                       16, 4, /* Important, largish objects */
                       svn_fs_x__serialize_noderevs_container,
                       svn_fs_x__deserialize_noderevs_container,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "NODEREVSCNT",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));
  SVN_ERR(create_cache(&(ffd->changes_container_cache),
                       NULL,
                       membuffer,
                       0, 0, /* Do not use inprocess cache */
                       svn_fs_x__serialize_changes_container,
                       svn_fs_x__deserialize_changes_container,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "CHANGESCNT",
                                   SVN_VA_NULL),
                       0,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));
  SVN_ERR(create_cache(&(ffd->reps_container_cache),
                       NULL,
                       membuffer,
                       0, 0, /* Do not use inprocess cache */
                       svn_fs_x__serialize_reps_container,
                       svn_fs_x__deserialize_reps_container,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "REPSCNT",
                                   SVN_VA_NULL),
                       0,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));

  /* Cache index info. */
  SVN_ERR(create_cache(&(ffd->l2p_header_cache),
                       NULL,
                       membuffer,
                       64, 16, /* entry size varies but we must cover
                                  a reasonable number of revisions (1k) */
                       svn_fs_x__serialize_l2p_header,
                       svn_fs_x__deserialize_l2p_header,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "L2P_HEADER",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));
  SVN_ERR(create_cache(&(ffd->l2p_page_cache),
                       NULL,
                       membuffer,
                       64, 16, /* entry size varies but we must cover
                                  a reasonable number of revisions (1k) */
                       svn_fs_x__serialize_l2p_page,
                       svn_fs_x__deserialize_l2p_page,
                       sizeof(svn_fs_x__page_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "L2P_PAGE",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));
  SVN_ERR(create_cache(&(ffd->p2l_header_cache),
                       NULL,
                       membuffer,
                       4, 1, /* Large entries. Rarely used. */
                       svn_fs_x__serialize_p2l_header,
                       svn_fs_x__deserialize_p2l_header,
                       sizeof(svn_fs_x__pair_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "P2L_HEADER",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));
  SVN_ERR(create_cache(&(ffd->p2l_page_cache),
                       NULL,
                       membuffer,
                       4, 16, /* Variably sized entries. Rarely used. */
                       svn_fs_x__serialize_p2l_page,
                       svn_fs_x__deserialize_p2l_page,
                       sizeof(svn_fs_x__page_cache_key_t),
                       apr_pstrcat(scratch_pool, prefix, "P2L_PAGE",
                                   SVN_VA_NULL),
                       SVN_CACHE__MEMBUFFER_HIGH_PRIORITY,
                       has_namespace,
                       fs,
                       no_handler, FALSE,
                       fs->pool, scratch_pool));

  return SVN_NO_ERROR;
}