#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
struct TYPE_10__ {int /*<<< orphan*/  change_set; } ;
struct TYPE_8__ {scalar_t__ number; } ;
struct TYPE_7__ {scalar_t__ number; } ;
struct TYPE_9__ {TYPE_5__ noderev_id; int /*<<< orphan*/  copyfrom_rev; int /*<<< orphan*/ * copyfrom_path; int /*<<< orphan*/  predecessor_count; TYPE_5__ predecessor_id; TYPE_2__ copy_id; TYPE_1__ node_id; } ;
typedef  TYPE_3__ svn_fs_x__noderev_t ;
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_x__get_node_revision (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__init_txn_root (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_fs_x__is_txn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_x__put_node_revision (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_new_txn_noderev_from_rev(svn_fs_t *fs,
                                svn_fs_x__txn_id_t txn_id,
                                svn_fs_x__id_t *src,
                                apr_pool_t *scratch_pool)
{
  svn_fs_x__noderev_t *noderev;
  SVN_ERR(svn_fs_x__get_node_revision(&noderev, fs, src, scratch_pool,
                                      scratch_pool));

  /* This must be a root node. */
  SVN_ERR_ASSERT(   noderev->node_id.number == 0
                 && noderev->copy_id.number == 0);

  if (svn_fs_x__is_txn(noderev->noderev_id.change_set))
    return svn_error_create(SVN_ERR_FS_CORRUPT, NULL,
                            _("Copying from transactions not allowed"));

  noderev->predecessor_id = noderev->noderev_id;
  noderev->predecessor_count++;
  noderev->copyfrom_path = NULL;
  noderev->copyfrom_rev = SVN_INVALID_REVNUM;

  /* For the transaction root, the copyroot never changes. */
  svn_fs_x__init_txn_root(&noderev->noderev_id, txn_id);

  return svn_fs_x__put_node_revision(fs, noderev, scratch_pool);
}