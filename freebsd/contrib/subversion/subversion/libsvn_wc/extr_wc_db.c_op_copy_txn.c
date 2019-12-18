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
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct op_copy_baton {int /*<<< orphan*/  work_items; int /*<<< orphan*/  dst_relpath; int /*<<< orphan*/ * dst_wcroot; int /*<<< orphan*/  src_relpath; int /*<<< orphan*/  src_wcroot; int /*<<< orphan*/  dst_op_root_relpath; scalar_t__ is_move; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_op_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int relpath_depth (int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
op_copy_txn(svn_wc__db_wcroot_t *wcroot,
            struct op_copy_baton *ocb,
            apr_pool_t *scratch_pool)
{
  int move_op_depth;

  if (wcroot != ocb->dst_wcroot)
    {
       /* Source and destination databases differ; so also start a lock
          in the destination database, by calling ourself in an extra lock. */

      SVN_WC__DB_WITH_TXN(op_copy_txn(ocb->dst_wcroot, ocb, scratch_pool),
                          ocb->dst_wcroot);

      return SVN_NO_ERROR;
    }

  /* From this point we can assume a lock in the src and dst databases */

  if (ocb->is_move)
    move_op_depth = relpath_depth(ocb->dst_op_root_relpath);
  else
    move_op_depth = 0;

  SVN_ERR(db_op_copy(ocb->src_wcroot, ocb->src_relpath,
                     ocb->dst_wcroot, ocb->dst_relpath,
                     ocb->work_items, move_op_depth, scratch_pool));

  return SVN_NO_ERROR;
}