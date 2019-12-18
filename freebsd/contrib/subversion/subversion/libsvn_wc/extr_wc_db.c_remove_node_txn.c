#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  wc_id; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  const svn_skel_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_8__ {scalar_t__ kind; scalar_t__ filesize; scalar_t__ mtime; } ;
typedef  TYPE_2__ svn_io_dirent2_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/ * (* svn_cancel_func_t ) (void*) ;
typedef  int svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  STMT_DELETE_ACTUAL_NODE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_DELETE_NODE_ALL_LAYERS ; 
 int /*<<< orphan*/  STMT_DELETE_NODE_RECURSIVE ; 
 int /*<<< orphan*/  STMT_SELECT_WORKING_PRESENT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int TRUE ; 
 int /*<<< orphan*/ * add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_recorded_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/ * read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_compose_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_io_stat_dirent2 (TYPE_2__ const**,char const*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__column_is_null (int /*<<< orphan*/ *,int) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_sqlite__column_token (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__db_mark_conflict_internal (TYPE_1__*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 
 int /*<<< orphan*/ * svn_wc__internal_file_modified_p (int*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__wq_build_dir_remove (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__wq_build_file_remove (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
remove_node_txn(svn_boolean_t *left_changes,
                svn_wc__db_wcroot_t *wcroot,
                const char *local_relpath,
                svn_wc__db_t *db,
                svn_boolean_t destroy_wc,
                svn_boolean_t destroy_changes,
                const svn_skel_t *conflict,
                const svn_skel_t *work_items,
                svn_cancel_func_t cancel_func,
                void *cancel_baton,
                apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;

  /* Note that unlike many similar functions it is a valid scenario for this
     function to be called on a wcroot! */

   /* db set when destroying wc */
  SVN_ERR_ASSERT(!destroy_wc || db != NULL);

  if (left_changes)
    *left_changes = FALSE;

  if (destroy_wc
      && (!destroy_changes || *local_relpath == '\0'))
    {
      svn_boolean_t have_row;
      apr_pool_t *iterpool;
      svn_error_t *err = NULL;

      /* Install WQ items for deleting the unmodified files and all dirs */
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_WORKING_PRESENT));
      SVN_ERR(svn_sqlite__bindf(stmt, "is",
                                wcroot->wc_id, local_relpath));

      SVN_ERR(svn_sqlite__step(&have_row, stmt));

      iterpool = svn_pool_create(scratch_pool);

      while (have_row)
        {
          const char *child_relpath;
          const char *child_abspath;
          svn_node_kind_t child_kind;
          svn_boolean_t have_checksum;
          svn_filesize_t recorded_size;
          apr_int64_t recorded_time;
          const svn_io_dirent2_t *dirent;
          svn_boolean_t modified_p = TRUE;
          svn_skel_t *work_item = NULL;

          svn_pool_clear(iterpool);

          child_relpath = svn_sqlite__column_text(stmt, 0, NULL);
          child_kind = svn_sqlite__column_token(stmt, 1, kind_map);

          child_abspath = svn_dirent_join(wcroot->abspath, child_relpath,
                                          iterpool);

          if (child_kind == svn_node_file)
            {
              have_checksum = !svn_sqlite__column_is_null(stmt, 2);
              recorded_size = get_recorded_size(stmt, 3);
              recorded_time = svn_sqlite__column_int64(stmt, 4);
            }

          if (cancel_func)
            err = cancel_func(cancel_baton);

          if (err)
            break;

          err = svn_io_stat_dirent2(&dirent, child_abspath, FALSE, TRUE,
                                    iterpool, iterpool);

          if (err)
            break;

          if (destroy_changes
              || dirent->kind != svn_node_file
              || child_kind != svn_node_file)
            {
              /* Not interested in keeping changes */
              modified_p = FALSE;
            }
          else if (child_kind == svn_node_file
                   && dirent->kind == svn_node_file
                   && dirent->filesize == recorded_size
                   && dirent->mtime == recorded_time)
            {
              modified_p = FALSE; /* File matches recorded state */
            }
          else if (have_checksum)
            err = svn_wc__internal_file_modified_p(&modified_p,
                                                   db, child_abspath,
                                                   FALSE, iterpool);

          if (err)
            break;

          if (modified_p)
            {
              if (left_changes)
                *left_changes = TRUE;
            }
          else if (child_kind == svn_node_dir)
            {
              err = svn_wc__wq_build_dir_remove(&work_item,
                                                db, wcroot->abspath,
                                                child_abspath, FALSE,
                                                iterpool, iterpool);
            }
          else /* svn_node_file || svn_node_symlink */
            {
              err = svn_wc__wq_build_file_remove(&work_item,
                                                 db, wcroot->abspath,
                                                 child_abspath,
                                                 iterpool, iterpool);
            }

          if (err)
            break;

          if (work_item)
            {
              err = add_work_items(wcroot->sdb, work_item, iterpool);
              if (err)
                break;
            }

          SVN_ERR(svn_sqlite__step(&have_row, stmt));
        }
      svn_pool_destroy(iterpool);

      SVN_ERR(svn_error_compose_create(err, svn_sqlite__reset(stmt)));
    }

  if (destroy_wc && *local_relpath != '\0')
    {
      /* Create work item for destroying the root */
      svn_wc__db_status_t status;
      svn_node_kind_t kind;
      SVN_ERR(read_info(&status, &kind, NULL, NULL, NULL, NULL, NULL, NULL,
                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                        wcroot, local_relpath,
                        scratch_pool, scratch_pool));

      if (status == svn_wc__db_status_normal
          || status == svn_wc__db_status_added
          || status == svn_wc__db_status_incomplete)
        {
          svn_skel_t *work_item = NULL;
          const char *local_abspath = svn_dirent_join(wcroot->abspath,
                                                          local_relpath,
                                                          scratch_pool);

          if (kind == svn_node_dir)
            {
              SVN_ERR(svn_wc__wq_build_dir_remove(&work_item,
                                                  db, wcroot->abspath,
                                                  local_abspath,
                                                  destroy_changes
                                                      /* recursive */,
                                                  scratch_pool, scratch_pool));
            }
          else
            {
              svn_boolean_t modified_p = FALSE;

              if (!destroy_changes)
                {
                  SVN_ERR(svn_wc__internal_file_modified_p(&modified_p,
                                                           db, local_abspath,
                                                           FALSE,
                                                           scratch_pool));
                }

              if (!modified_p)
                SVN_ERR(svn_wc__wq_build_file_remove(&work_item,
                                                     db, wcroot->abspath,
                                                     local_abspath,
                                                     scratch_pool,
                                                     scratch_pool));
              else
                {
                  if (left_changes)
                    *left_changes = TRUE;
                }
            }

          SVN_ERR(add_work_items(wcroot->sdb, work_item, scratch_pool));
        }
    }

  /* Remove all nodes below local_relpath */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_DELETE_NODE_RECURSIVE));
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
  SVN_ERR(svn_sqlite__step_done(stmt));

  /* Delete the root NODE when this is not the working copy root */
  if (local_relpath[0] != '\0')
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_DELETE_NODE_ALL_LAYERS));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_DELETE_ACTUAL_NODE_RECURSIVE));

  /* Delete all actual nodes at or below local_relpath */
  SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id,
                                         local_relpath));
  SVN_ERR(svn_sqlite__step_done(stmt));

  SVN_ERR(add_work_items(wcroot->sdb, work_items, scratch_pool));
  if (conflict)
    SVN_ERR(svn_wc__db_mark_conflict_internal(wcroot, local_relpath,
                                              conflict, scratch_pool));

  return SVN_NO_ERROR;
}