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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_mergeinfo_receiver_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct get_mergeinfo_data_and_entries_baton {char const* node_path; void* receiver_baton; int /*<<< orphan*/  receiver; int /*<<< orphan*/ * node; int /*<<< orphan*/ * children_atop_mergeinfo_trees; } ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,void const**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/ * svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct get_mergeinfo_data_and_entries_baton*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_fspath__join (char const*,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_get_mergeinfo_data_and_entries ; 

__attribute__((used)) static svn_error_t *
crawl_directory_for_mergeinfo(svn_fs_t *fs,
                              dag_node_t *node,
                              const char *node_path,
                              svn_fs_mergeinfo_receiver_t receiver,
                              void *baton,
                              apr_pool_t *pool)
{
  struct get_mergeinfo_data_and_entries_baton gmdae_args;
  apr_hash_t *children_atop_mergeinfo_trees = apr_hash_make(pool);
  apr_hash_index_t *hi;
  apr_pool_t *iterpool;

  /* Add mergeinfo for immediate children that have it, and fetch
     immediate children that *don't* have it but sit atop trees that do. */
  gmdae_args.children_atop_mergeinfo_trees = children_atop_mergeinfo_trees;
  gmdae_args.node = node;
  gmdae_args.node_path = node_path;
  gmdae_args.receiver = receiver;
  gmdae_args.receiver_baton = baton;
  SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_get_mergeinfo_data_and_entries,
                                 &gmdae_args, FALSE, pool));

  /* If no children sit atop trees with mergeinfo, we're done.
     Otherwise, recurse on those children. */

  if (apr_hash_count(children_atop_mergeinfo_trees) == 0)
    return SVN_NO_ERROR;

  iterpool = svn_pool_create(pool);
  for (hi = apr_hash_first(pool, children_atop_mergeinfo_trees);
       hi;
       hi = apr_hash_next(hi))
    {
      const void *key;
      void *val;
      svn_pool_clear(iterpool);
      apr_hash_this(hi, &key, NULL, &val);
      SVN_ERR(crawl_directory_for_mergeinfo(fs, val,
                                            svn_fspath__join(node_path, key,
                                                             iterpool),
                                            receiver, baton, iterpool));
    }
  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}