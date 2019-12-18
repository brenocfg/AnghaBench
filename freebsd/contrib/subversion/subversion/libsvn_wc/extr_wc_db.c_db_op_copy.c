#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  wc_id; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_24__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INSERT_NODE ; 
 int /*<<< orphan*/  STMT_INSERT_WORKING_NODE_COPY_FROM ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  STMT_SELECT_OP_DEPTH_CHILDREN ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_actual (TYPE_1__*,char const*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cross_db_copy (TYPE_1__*,char const*,TYPE_1__*,char const*,int,int,int,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gather_children (int /*<<< orphan*/  const**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_info_for_copy (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int*,scalar_t__*,int*,TYPE_1__*,char const*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_incomplete_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  op_depth_for_copy (int*,int*,int*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  op_depth_of (int*,TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 TYPE_2__* read_info (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ svn_sqlite__column_boolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
#define  svn_wc__db_status_added 135 
#define  svn_wc__db_status_copied 134 
#define  svn_wc__db_status_deleted 133 
#define  svn_wc__db_status_excluded 132 
#define  svn_wc__db_status_moved_here 131 
#define  svn_wc__db_status_normal 130 
#define  svn_wc__db_status_not_present 129 
#define  svn_wc__db_status_server_excluded 128 

__attribute__((used)) static svn_error_t *
db_op_copy(svn_wc__db_wcroot_t *src_wcroot,
           const char *src_relpath,
           svn_wc__db_wcroot_t *dst_wcroot,
           const char *dst_relpath,
           const svn_skel_t *work_items,
           int move_op_depth,
           apr_pool_t *scratch_pool)
{
  const char *copyfrom_relpath;
  svn_revnum_t copyfrom_rev;
  svn_wc__db_status_t status;
  svn_wc__db_status_t dst_presence;
  svn_boolean_t op_root;
  apr_int64_t copyfrom_id;
  int dst_op_depth;
  int dst_np_op_depth;
  int dst_parent_op_depth;
  svn_node_kind_t kind;
  const apr_array_header_t *children;

  SVN_ERR(get_info_for_copy(&copyfrom_id, &copyfrom_relpath, &copyfrom_rev,
                            &status, &kind, &op_root,
                            src_wcroot, src_relpath, dst_wcroot,
                            scratch_pool, scratch_pool));

  SVN_ERR(op_depth_for_copy(&dst_op_depth, &dst_np_op_depth,
                            &dst_parent_op_depth,
                            copyfrom_id, copyfrom_relpath, copyfrom_rev,
                            dst_wcroot, dst_relpath, scratch_pool));

  SVN_ERR_ASSERT(kind == svn_node_file || kind == svn_node_dir);

  /* ### New status, not finished, see notes/wc-ng/copying */
  switch (status)
    {
    case svn_wc__db_status_normal:
    case svn_wc__db_status_added:
    case svn_wc__db_status_moved_here:
    case svn_wc__db_status_copied:
      dst_presence = svn_wc__db_status_normal;
      break;
    case svn_wc__db_status_deleted:
      if (op_root)
        {
          /* If the lower layer is already shadowcopied we can skip adding
             a not present node. */
          svn_error_t *err;
          svn_wc__db_status_t dst_status;

          err = read_info(&dst_status, NULL, NULL, NULL, NULL, NULL, NULL,
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                          dst_wcroot, dst_relpath, scratch_pool, scratch_pool);

          if (err)
            {
              if (err->apr_err == SVN_ERR_WC_PATH_NOT_FOUND)
                svn_error_clear(err);
              else
                return svn_error_trace(err);
            }
          else if (dst_status == svn_wc__db_status_deleted)
            {
              /* Node is already deleted; skip the NODES work, but do
                 install wq items if requested */
              SVN_ERR(add_work_items(dst_wcroot->sdb, work_items,
                                     scratch_pool));
              return SVN_NO_ERROR;
            }
        }
      else
        {
          /* This node is either a not-present node (which should be copied), or
             a base-delete of some lower layer (which shouldn't).
             Subversion <= 1.7 always added a not-present node here, which is
             safe (as it postpones the hard work until commit time and then we
             ask the repository), but it breaks some move scenarios.
             */

           if (! copyfrom_relpath)
             {
               SVN_ERR(add_work_items(dst_wcroot->sdb, work_items,
                                     scratch_pool));
               return SVN_NO_ERROR;
             }

           /* Fall through. Install not present node */
        }
    case svn_wc__db_status_not_present:
    case svn_wc__db_status_excluded:
      /* These presence values should not create a new op depth */
      if (dst_np_op_depth > 0)
        {
          dst_op_depth = dst_np_op_depth;
          dst_np_op_depth = -1;
        }
      if (status == svn_wc__db_status_excluded)
        dst_presence = svn_wc__db_status_excluded;
      else
        dst_presence = svn_wc__db_status_not_present;
      break;
    case svn_wc__db_status_server_excluded:
      return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                               _("Cannot copy '%s' excluded by server"),
                               path_for_error_message(src_wcroot,
                                                      src_relpath,
                                                      scratch_pool));
    default:
      /* Perhaps we should allow incomplete to incomplete? We can't
         avoid incomplete working nodes as one step in copying a
         directory is to add incomplete children. */
      return svn_error_createf(SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                               _("Cannot handle status of '%s'"),
                               path_for_error_message(src_wcroot,
                                                      src_relpath,
                                                      scratch_pool));
    }

  if (kind == svn_node_dir)
    {
      int src_op_depth;

      SVN_ERR(op_depth_of(&src_op_depth, src_wcroot, src_relpath));
      SVN_ERR(gather_children(&children, src_wcroot, src_relpath,
                              STMT_SELECT_OP_DEPTH_CHILDREN, src_op_depth,
                              scratch_pool, scratch_pool));
    }
  else
    children = NULL;

  if (src_wcroot == dst_wcroot)
    {
      svn_sqlite__stmt_t *stmt;
      const char *dst_parent_relpath = svn_relpath_dirname(dst_relpath,
                                                           scratch_pool);

      SVN_ERR(svn_sqlite__get_statement(&stmt, src_wcroot->sdb,
                                        STMT_INSERT_WORKING_NODE_COPY_FROM));

      SVN_ERR(svn_sqlite__bindf(stmt, "issdst",
                    src_wcroot->wc_id, src_relpath,
                    dst_relpath,
                    dst_op_depth,
                    dst_parent_relpath,
                    presence_map, dst_presence));

      if (move_op_depth > 0)
        {
          if (relpath_depth(dst_relpath) == move_op_depth)
            {
              /* We're moving the root of the move operation.
               *
               * When an added node or the op-root of a copy is moved,
               * there is no 'moved-from' corresponding to the moved-here
               * node. So the net effect is the same as copy+delete.
               * Perform a normal copy operation in these cases. */
              if (!(status == svn_wc__db_status_added ||
                    (status == svn_wc__db_status_copied && op_root)))
                SVN_ERR(svn_sqlite__bind_int(stmt, 7, 1));
            }
          else
            {
              svn_sqlite__stmt_t *info_stmt;
              svn_boolean_t have_row;

              /* We're moving a child along with the root of the move.
               *
               * Set moved-here depending on dst_parent, propagating the
               * above decision to moved-along children at the same op_depth.
               * We can't use scan_addition() to detect moved-here because
               * the delete-half of the move might not yet exist. */
              SVN_ERR(svn_sqlite__get_statement(&info_stmt, dst_wcroot->sdb,
                                                STMT_SELECT_NODE_INFO));
              SVN_ERR(svn_sqlite__bindf(info_stmt, "is", dst_wcroot->wc_id,
                                        dst_parent_relpath));
              SVN_ERR(svn_sqlite__step(&have_row, info_stmt));
              SVN_ERR_ASSERT(have_row);
              if (svn_sqlite__column_boolean(info_stmt, 15) &&
                  dst_op_depth == dst_parent_op_depth)
                {
                  SVN_ERR(svn_sqlite__bind_int(stmt, 7, 1));
                  SVN_ERR(svn_sqlite__reset(info_stmt));
                }
              else
                {
                  SVN_ERR(svn_sqlite__reset(info_stmt));

                  /* If the child has been moved into the tree we're moving,
                   * keep its moved-here bit set. */
                  SVN_ERR(svn_sqlite__get_statement(&info_stmt,
                                                    dst_wcroot->sdb,
                                                    STMT_SELECT_NODE_INFO));
                  SVN_ERR(svn_sqlite__bindf(info_stmt, "is",
                                            dst_wcroot->wc_id, src_relpath));
                  SVN_ERR(svn_sqlite__step(&have_row, info_stmt));
                  SVN_ERR_ASSERT(have_row);
                  if (svn_sqlite__column_boolean(info_stmt, 15))
                    SVN_ERR(svn_sqlite__bind_int(stmt, 7, 1));
                  SVN_ERR(svn_sqlite__reset(info_stmt));
                }
            }
        }

      SVN_ERR(svn_sqlite__step_done(stmt));

      /* ### Copying changelist is OK for a move but what about a copy? */
      SVN_ERR(copy_actual(src_wcroot, src_relpath,
                          dst_wcroot, dst_relpath, scratch_pool));

      if (dst_np_op_depth > 0)
        {
          /* We introduce a not-present node at the parent's op_depth to
             properly start a new op-depth at our own op_depth. This marks
             us as an op_root for commit and allows reverting just this
             operation */

          SVN_ERR(svn_sqlite__get_statement(&stmt, dst_wcroot->sdb,
                                            STMT_INSERT_NODE));
          SVN_ERR(svn_sqlite__bindf(stmt, "isdsisrtnt",
                                    src_wcroot->wc_id, dst_relpath,
                                    dst_np_op_depth, dst_parent_relpath,
                                    copyfrom_id, copyfrom_relpath,
                                    copyfrom_rev,
                                    presence_map,
                                       svn_wc__db_status_not_present,
                                    /* NULL */
                                    kind_map, kind));

          SVN_ERR(svn_sqlite__step_done(stmt));
        }
      /* Insert incomplete children, if relevant.
         The children are part of the same op and so have the same op_depth.
         (The only time we'd want a different depth is during a recursive
         simple add, but we never insert children here during a simple add.) */
      if (kind == svn_node_dir
          && dst_presence == svn_wc__db_status_normal)
        SVN_ERR(insert_incomplete_children(
                  dst_wcroot->sdb,
                  dst_wcroot->wc_id,
                  dst_relpath,
                  copyfrom_id,
                  copyfrom_relpath,
                  copyfrom_rev,
                  children,
                  dst_op_depth,
                  scratch_pool));
    }
  else
    {
      SVN_ERR(cross_db_copy(src_wcroot, src_relpath, dst_wcroot,
                            dst_relpath, dst_presence, dst_op_depth,
                            dst_np_op_depth, kind,
                            children, copyfrom_id, copyfrom_relpath,
                            copyfrom_rev, scratch_pool));
    }

  SVN_ERR(add_work_items(dst_wcroot->sdb, work_items, scratch_pool));

  return SVN_NO_ERROR;
}