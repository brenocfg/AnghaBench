#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
struct TYPE_35__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  wc_id; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_36__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct insert_base_baton_t {char const* repos_relpath; int /*<<< orphan*/ * target; int /*<<< orphan*/ * checksum; int /*<<< orphan*/  depth; int /*<<< orphan*/ * children; int /*<<< orphan*/  revision; scalar_t__ kind; int /*<<< orphan*/  status; int /*<<< orphan*/  repos_id; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_FOR_BASE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_NODE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_BASE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_WORKING_BASE_DELETE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_WORKING_RECURSIVE ; 
 int /*<<< orphan*/  STMT_SELECT_MOVED_DESCENDANTS_SRC ; 
 int /*<<< orphan*/  STMT_SELECT_MOVED_OUTSIDE ; 
 int /*<<< orphan*/  STMT_SELECT_NODE_INFO ; 
 int /*<<< orphan*/  STMT_SELECT_WORKING_PRESENT ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 TYPE_2__* add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blank_ibb (struct insert_base_baton_t*) ; 
 TYPE_2__* clear_moved_here (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* db_retract_parent_delete (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* insert_base_node (struct insert_base_baton_t*,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  presence_map ; 
 int relpath_depth (char const*) ; 
 int /*<<< orphan*/  svn_depth_unknown ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_compose_create (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 char* svn_relpath_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_relpath_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_base_get_info_internal (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_mark_conflict_internal (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_op_break_move_internal (TYPE_1__*,char const*,int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_op_make_copy_internal (TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_base_deleted ; 
 int /*<<< orphan*/  svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 
 int /*<<< orphan*/  svn_wc__db_status_not_present ; 
 TYPE_2__* svn_wc__wq_build_dir_remove (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__wq_build_file_remove (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
db_base_remove(svn_wc__db_wcroot_t *wcroot,
               const char *local_relpath,
               svn_wc__db_t *db, /* For checking conflicts */
               svn_boolean_t keep_as_working,
               svn_boolean_t mark_not_present,
               svn_boolean_t mark_excluded,
               svn_revnum_t marker_revision,
               svn_skel_t *conflict,
               svn_skel_t *work_items,
               apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;
  svn_wc__db_status_t status;
  svn_revnum_t revision;
  apr_int64_t repos_id;
  const char *repos_relpath;
  svn_node_kind_t kind;
  svn_boolean_t keep_working;
  int op_depth;
  svn_node_kind_t wrk_kind;
  svn_boolean_t no_delete_wc = FALSE;
  svn_boolean_t file_external;

  SVN_ERR(svn_wc__db_base_get_info_internal(&status, &kind, &revision,
                                            &repos_relpath, &repos_id,
                                            NULL, NULL, NULL, NULL, NULL,
                                            NULL, NULL, NULL, NULL,
                                            &file_external,
                                            wcroot, local_relpath,
                                            scratch_pool, scratch_pool));

  /* Check if there is already a working node */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_SELECT_NODE_INFO));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));

  if (!have_row)
    return svn_error_trace(svn_sqlite__reset(stmt)); /* No BASE */

  op_depth = svn_sqlite__column_int(stmt, 0);
  wrk_kind = svn_sqlite__column_token(stmt, 4, kind_map);

  if (op_depth > 0
      && op_depth == relpath_depth(local_relpath))
    {
      svn_wc__db_status_t presence;
      presence = svn_sqlite__column_token(stmt, 3, presence_map);

      if (presence == svn_wc__db_status_base_deleted)
        {
          keep_working = FALSE;
          no_delete_wc = TRUE;
        }
      else
        {
          keep_working = TRUE;
        }
    }
  else
    keep_working = FALSE;
  SVN_ERR(svn_sqlite__reset(stmt));

  if (keep_as_working && op_depth == 0)
    {
      if (status == svn_wc__db_status_normal
          || status == svn_wc__db_status_incomplete)
        {
          SVN_ERR(svn_wc__db_op_make_copy_internal(wcroot, local_relpath, TRUE,
                                                   NULL, NULL,
                                                   scratch_pool));
        }
      keep_working = TRUE;
    }

  /* Step 1: Create workqueue operations to remove files and dirs in the
     local-wc */
  if (!keep_working && !no_delete_wc)
    {
      svn_skel_t *work_item;
      const char *local_abspath;

      local_abspath = svn_dirent_join(wcroot->abspath, local_relpath,
                                      scratch_pool);
      if (wrk_kind == svn_node_dir)
        {
          apr_pool_t *iterpool;
          SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                            STMT_SELECT_WORKING_PRESENT));
          SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

          iterpool = svn_pool_create(scratch_pool);

          SVN_ERR(svn_sqlite__step(&have_row, stmt));

          while (have_row)
            {
              const char *node_relpath = svn_sqlite__column_text(stmt, 0, NULL);
              svn_node_kind_t node_kind = svn_sqlite__column_token(stmt, 1,
                                                              kind_map);
              const char *node_abspath;
              svn_error_t *err;

              svn_pool_clear(iterpool);

              node_abspath = svn_dirent_join(wcroot->abspath, node_relpath,
                                             iterpool);

              if (node_kind == svn_node_dir)
                err = svn_wc__wq_build_dir_remove(&work_item,
                                                  db, wcroot->abspath,
                                                  node_abspath, FALSE,
                                                  iterpool, iterpool);
              else
                err = svn_wc__wq_build_file_remove(&work_item,
                                                   db,
                                                   wcroot->abspath,
                                                   node_abspath,
                                                   iterpool, iterpool);

              if (!err)
                err = add_work_items(wcroot->sdb, work_item, iterpool);
              if (err)
                return svn_error_compose_create(err, svn_sqlite__reset(stmt));

              SVN_ERR(svn_sqlite__step(&have_row, stmt));
           }

          SVN_ERR(svn_sqlite__reset(stmt));

          SVN_ERR(svn_wc__wq_build_dir_remove(&work_item,
                                              db, wcroot->abspath,
                                              local_abspath, FALSE,
                                              scratch_pool, iterpool));
          svn_pool_destroy(iterpool);
        }
      else
        SVN_ERR(svn_wc__wq_build_file_remove(&work_item,
                                             db, wcroot->abspath,
                                             local_abspath,
                                             scratch_pool, scratch_pool));

      SVN_ERR(add_work_items(wcroot->sdb, work_item, scratch_pool));
    }

  /* Step 2: Delete ACTUAL nodes */
  if (! keep_working)
    {
      /* There won't be a record in NODE left for this node, so we want
         to remove *all* ACTUAL nodes, including ACTUAL ONLY. */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_ACTUAL_NODE_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }
  else if (! keep_as_working)
    {
      /* Delete only the ACTUAL nodes that apply to a delete of a BASE node */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                       STMT_DELETE_ACTUAL_FOR_BASE_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }
  /* Else: Everything has been turned into a copy, so we want to keep all
           ACTUAL_NODE records */

  /* Step 3: Delete WORKING nodes */
  if (!keep_working)
    {
      apr_pool_t *iterpool;

      /* When deleting everything in working we should break moves from
         here and to here.
       */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_MOVED_OUTSIDE));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                                             local_relpath,
                                             relpath_depth(local_relpath)));
      SVN_ERR(svn_sqlite__step(&have_row, stmt));
      iterpool = svn_pool_create(scratch_pool);
      while (have_row)
        {
          const char *moved_to_relpath;
          svn_error_t *err;

          svn_pool_clear(iterpool);
          moved_to_relpath = svn_sqlite__column_text(stmt, 1, iterpool);
          err = clear_moved_here(wcroot, moved_to_relpath, iterpool);
          if (err)
            return svn_error_compose_create(err, svn_sqlite__reset(stmt));
          SVN_ERR(svn_sqlite__step(&have_row, stmt));
        }
      svn_pool_destroy(iterpool);
      SVN_ERR(svn_sqlite__reset(stmt));
    }
  else
    {
      /* We are keeping things that are in WORKING, but we should still
         break moves of things in BASE. (Mixed revisions make it
         impossible to guarantee that we can keep everything moved) */

      apr_pool_t *iterpool;

      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_MOVED_DESCENDANTS_SRC));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id,
                                local_relpath, 0));
      SVN_ERR(svn_sqlite__step(&have_row, stmt));
      iterpool = svn_pool_create(scratch_pool);
      while (have_row)
        {
          int delete_op_depth = svn_sqlite__column_int(stmt, 0);
          const char *src_relpath;
          const char *dst_relpath;
          svn_error_t *err;

          svn_pool_clear(iterpool);

          src_relpath = svn_sqlite__column_text(stmt, 1, iterpool);
          dst_relpath = svn_sqlite__column_text(stmt, 4, iterpool);

          err = svn_wc__db_op_break_move_internal(wcroot, src_relpath,
                                                  delete_op_depth,
                                                  dst_relpath,
                                                  NULL,
                                                  iterpool);

          if (err)
            return svn_error_compose_create(err, svn_sqlite__reset(stmt));

          SVN_ERR(svn_sqlite__step(&have_row, stmt));
        }
      svn_pool_destroy(iterpool);
      SVN_ERR(svn_sqlite__reset(stmt));
    }
  if (keep_working)
    {
      SVN_ERR(svn_sqlite__get_statement(
                    &stmt, wcroot->sdb,
                    STMT_DELETE_WORKING_BASE_DELETE_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd", wcroot->wc_id, local_relpath, 0));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }
  else
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_WORKING_RECURSIVE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  /* Step 4: Delete the BASE node descendants */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_DELETE_BASE_RECURSIVE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step_done(stmt));

  SVN_ERR(db_retract_parent_delete(wcroot, local_relpath, 0, scratch_pool));

  if (mark_not_present || mark_excluded)
    {
      struct insert_base_baton_t ibb;
      svn_boolean_t no_marker = FALSE;

      if (file_external)
        {
          const char *parent_local_relpath;
          const char *name;
          svn_error_t *err;

          /* For file externals we only want to place a not present marker
             if there is a BASE parent */
          
          svn_relpath_split(&parent_local_relpath, &name, local_relpath,
                            scratch_pool);

          err = svn_wc__db_base_get_info_internal(NULL, NULL, NULL,
                                                  &repos_relpath, &repos_id,
                                                  NULL, NULL, NULL, NULL, NULL,
                                                  NULL, NULL, NULL, NULL, NULL,
                                                  wcroot, parent_local_relpath,
                                                  scratch_pool, scratch_pool);

          if (err && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
            return svn_error_trace(err);
          else if (err)
            {
              svn_error_clear(err);
              no_marker = TRUE;
            }
          else
            {
              /* Replace the repos_relpath with something more expected than
                 the unrelated old file external repository relpath, which
                 one day may come from a different repository */
              repos_relpath = svn_relpath_join(repos_relpath, name, scratch_pool);
            }
        }

      if (!no_marker)
        {
          blank_ibb(&ibb);

          ibb.repos_id = repos_id;
          ibb.status = mark_excluded ? svn_wc__db_status_excluded
                                     : svn_wc__db_status_not_present;
          ibb.kind = kind;
          ibb.repos_relpath = repos_relpath;
          ibb.revision = SVN_IS_VALID_REVNUM(marker_revision)
                            ? marker_revision
                            : revision;

          /* Depending upon KIND, any of these might get used. */
          ibb.children = NULL;
          ibb.depth = svn_depth_unknown;
          ibb.checksum = NULL;
          ibb.target = NULL;

          SVN_ERR(insert_base_node(&ibb, wcroot, local_relpath, scratch_pool));
        }
    }

  SVN_ERR(add_work_items(wcroot->sdb, work_items, scratch_pool));
  if (conflict)
    SVN_ERR(svn_wc__db_mark_conflict_internal(wcroot, local_relpath,
                                              conflict, scratch_pool));

  return SVN_NO_ERROR;
}