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
struct TYPE_7__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct text_baton_t {int /*<<< orphan*/  node; int /*<<< orphan*/  path; TYPE_1__* root; int /*<<< orphan*/  result_checksum; } ;
struct TYPE_6__ {int /*<<< orphan*/  txn; int /*<<< orphan*/  fs; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * add_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_finalize_edits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_base__dag_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_path_change_modify ; 

__attribute__((used)) static svn_error_t *
txn_body_fulltext_finalize_edits(void *baton, trail_t *trail)
{
  struct text_baton_t *tb = baton;
  SVN_ERR(svn_fs_base__dag_finalize_edits(tb->node,
                                          tb->result_checksum,
                                          tb->root->txn,
                                          trail, trail->pool));

  /* Make a record of this modification in the changes table. */
  return add_change(tb->root->fs, tb->root->txn, tb->path,
                    svn_fs_base__dag_get_id(tb->node),
                    svn_fs_path_change_modify, TRUE, FALSE, trail,
                    trail->pool);
}