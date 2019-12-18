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
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  fs; } ;
typedef  TYPE_1__ trail_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct txn_pred_count_args {int /*<<< orphan*/  pred_count; int /*<<< orphan*/  id; } ;
struct TYPE_7__ {int /*<<< orphan*/  predecessor_count; } ;
typedef  TYPE_2__ node_revision_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_fs_bdb__get_node_revision (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
txn_body_pred_count(void *baton, trail_t *trail)
{
  node_revision_t *noderev;
  struct txn_pred_count_args *args = baton;

  SVN_ERR(svn_fs_bdb__get_node_revision(&noderev, trail->fs,
                                        args->id, trail, trail->pool));
  args->pred_count = noderev->predecessor_count;
  return SVN_NO_ERROR;
}