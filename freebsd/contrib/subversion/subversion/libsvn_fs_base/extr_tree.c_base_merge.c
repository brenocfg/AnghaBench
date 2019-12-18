#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_txn_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_17__ {int /*<<< orphan*/  txn; int /*<<< orphan*/ * fs; int /*<<< orphan*/  is_txn_root; } ;
typedef  TYPE_1__ svn_fs_root_t ;
struct TYPE_18__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct merge_args {TYPE_3__* conflict; int /*<<< orphan*/ * txn; int /*<<< orphan*/ * ancestor_node; int /*<<< orphan*/ * source_node; int /*<<< orphan*/ * node; TYPE_1__* root; } ;
struct get_root_args {TYPE_3__* conflict; int /*<<< orphan*/ * txn; int /*<<< orphan*/ * ancestor_node; int /*<<< orphan*/ * source_node; int /*<<< orphan*/ * node; TYPE_1__* root; } ;
typedef  int /*<<< orphan*/  dag_node_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_19__ {char* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_FS_CONFLICT ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 TYPE_2__* SVN_FS__NOT_TXN (TYPE_1__*) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_fs_base__open_txn (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_fs_base__retry_txn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct merge_args*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_stringbuf_create_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txn_body_get_root ; 
 int /*<<< orphan*/  txn_body_merge ; 

__attribute__((used)) static svn_error_t *
base_merge(const char **conflict_p,
           svn_fs_root_t *source_root,
           const char *source_path,
           svn_fs_root_t *target_root,
           const char *target_path,
           svn_fs_root_t *ancestor_root,
           const char *ancestor_path,
           apr_pool_t *pool)
{
  dag_node_t *source, *ancestor;
  struct get_root_args get_root_args;
  struct merge_args merge_args;
  svn_fs_txn_t *txn;
  svn_error_t *err;
  svn_fs_t *fs;

  if (! target_root->is_txn_root)
    return SVN_FS__NOT_TXN(target_root);

  /* Paranoia. */
  fs = ancestor_root->fs;
  if ((source_root->fs != fs) || (target_root->fs != fs))
    {
      return svn_error_create
        (SVN_ERR_FS_CORRUPT, NULL,
         _("Bad merge; ancestor, source, and target not all in same fs"));
    }

  /* ### kff todo: is there any compelling reason to get the nodes in
     one db transaction?  Right now we don't; txn_body_get_root() gets
     one node at a time.  This will probably need to change:

     Jim Blandy <jimb@zwingli.cygnus.com> writes:
     > svn_fs_merge needs to be a single transaction, to protect it against
     > people deleting parents of nodes it's working on, etc.
  */

  /* Get the ancestor node. */
  get_root_args.root = ancestor_root;
  SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_get_root, &get_root_args,
                                 FALSE, pool));
  ancestor = get_root_args.node;

  /* Get the source node. */
  get_root_args.root = source_root;
  SVN_ERR(svn_fs_base__retry_txn(fs, txn_body_get_root, &get_root_args,
                                 FALSE, pool));
  source = get_root_args.node;

  /* Open a txn for the txn root into which we're merging. */
  SVN_ERR(svn_fs_base__open_txn(&txn, fs, target_root->txn, pool));

  /* Merge changes between ANCESTOR and SOURCE into TXN. */
  merge_args.source_node = source;
  merge_args.ancestor_node = ancestor;
  merge_args.txn = txn;
  merge_args.conflict = svn_stringbuf_create_empty(pool);
  err = svn_fs_base__retry_txn(fs, txn_body_merge, &merge_args, FALSE, pool);
  if (err)
    {
      if ((err->apr_err == SVN_ERR_FS_CONFLICT) && conflict_p)
        *conflict_p = merge_args.conflict->data;
      return svn_error_trace(err);
    }

  return SVN_NO_ERROR;
}