#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
struct TYPE_8__ {int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ svn_fs_dirent_t ;
struct TYPE_9__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct remove_node_args {char const* txn_id; int /*<<< orphan*/  const* id; int /*<<< orphan*/ ** dirents; } ;
struct get_dirents_args {char const* txn_id; int /*<<< orphan*/  const* id; int /*<<< orphan*/ ** dirents; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_FS_ID_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_base__id_txn_id (int /*<<< orphan*/  const*) ; 
 TYPE_2__* svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct remove_node_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_get_dirents ; 
 int /*<<< orphan*/  txn_body_remove_node ; 

__attribute__((used)) static svn_error_t *
delete_txn_tree(svn_fs_t *fs,
                const svn_fs_id_t *id,
                const char *txn_id,
                apr_pool_t *pool)
{
  struct get_dirents_args dirent_args;
  struct remove_node_args rm_args;
  apr_hash_t *dirents = NULL;
  apr_hash_index_t *hi;
  svn_error_t *err;

  /* If this sucker isn't mutable, there's nothing to do. */
  if (strcmp(svn_fs_base__id_txn_id(id), txn_id) != 0)
    return SVN_NO_ERROR;

  /* See if the thing has dirents that need to be recursed upon.  If
     you can't find the thing itself, don't sweat it.  We probably
     already cleaned it up. */
  dirent_args.dirents = &dirents;
  dirent_args.id = id;
  dirent_args.txn_id = txn_id;
  err = svn_fs_base__retry_txn(fs, txn_body_get_dirents, &dirent_args,
                               FALSE, pool);
  if (err && (err->apr_err == SVN_ERR_FS_ID_NOT_FOUND))
    {
      svn_error_clear(err);
      return SVN_NO_ERROR;
    }
  SVN_ERR(err);

  /* If there are dirents upon which to recurse ... recurse. */
  if (dirents)
    {
      apr_pool_t *subpool = svn_pool_create(pool);

      /* Loop over hash entries */
      for (hi = apr_hash_first(pool, dirents); hi; hi = apr_hash_next(hi))
        {
          void *val;
          svn_fs_dirent_t *dirent;

          svn_pool_clear(subpool);
          apr_hash_this(hi, NULL, NULL, &val);
          dirent = val;
          SVN_ERR(delete_txn_tree(fs, dirent->id, txn_id, subpool));
        }
      svn_pool_destroy(subpool);
    }

  /* Remove the node. */
  rm_args.id = id;
  rm_args.txn_id = txn_id;
  return svn_fs_base__retry_txn(fs, txn_body_remove_node, &rm_args,
                                TRUE, pool);
}