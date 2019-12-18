#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  prop_rep; int /*<<< orphan*/  data_rep; int /*<<< orphan*/  is_fresh_txn_root; } ;
typedef  TYPE_1__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_fs__fixup_expanded_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
fixup_node_revision(svn_fs_t *fs,
                    node_revision_t *noderev,
                    apr_pool_t *scratch_pool)
{
  /* Workaround issue #4031: is-fresh-txn-root in revision files. */
  noderev->is_fresh_txn_root = FALSE;

  /* Make sure EXPANDED_SIZE has the correct value for every rep. */
  SVN_ERR(svn_fs_fs__fixup_expanded_size(fs, noderev->data_rep,
                                         scratch_pool));
  SVN_ERR(svn_fs_fs__fixup_expanded_size(fs, noderev->prop_rep,
                                         scratch_pool));

  return SVN_NO_ERROR;
}