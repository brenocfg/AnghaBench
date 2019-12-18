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
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_4__ {int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ svn_fs_root_t ;
struct TYPE_5__ {int /*<<< orphan*/  kind; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ svn_fs_dirent_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct node_kind_args {char const* path; int /*<<< orphan*/  kind; int /*<<< orphan*/  id; TYPE_1__* root; int /*<<< orphan*/ ** table_p; } ;
struct dir_entries_args {char const* path; int /*<<< orphan*/  kind; int /*<<< orphan*/  id; TYPE_1__* root; int /*<<< orphan*/ ** table_p; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct node_kind_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_dir_entries ; 
 int /*<<< orphan*/  txn_body_node_kind ; 

__attribute__((used)) static svn_error_t *
base_dir_entries(apr_hash_t **table_p,
                 svn_fs_root_t *root,
                 const char *path,
                 apr_pool_t *pool)
{
  struct dir_entries_args args;
  apr_pool_t *iterpool;
  apr_hash_t *table;
  svn_fs_t *fs = root->fs;
  apr_hash_index_t *hi;

  args.table_p = &table;
  args.root    = root;
  args.path    = path;
  SVN_ERR(svn_fs_base__retry_txn(root->fs, txn_body_dir_entries, &args,
                                 FALSE, pool));

  iterpool = svn_pool_create(pool);

  /* Add in the kind data. */
  for (hi = apr_hash_first(pool, table); hi; hi = apr_hash_next(hi))
    {
      svn_fs_dirent_t *entry;
      struct node_kind_args nk_args;
      void *val;

      svn_pool_clear(iterpool);

      /* KEY will be the entry name in ancestor (about which we
         simply don't care), VAL the dirent. */
      apr_hash_this(hi, NULL, NULL, &val);
      entry = val;
      nk_args.id = entry->id;

      /* We don't need to have the retry function destroy the trail
         pool because we're already doing that via the use of an
         iteration pool. */
      SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_node_kind, &nk_args,
                                     FALSE, iterpool));
      entry->kind = nk_args.kind;
    }

  svn_pool_destroy(iterpool);

  *table_p = table;
  return SVN_NO_ERROR;
}