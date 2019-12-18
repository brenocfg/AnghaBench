#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  abspath; int /*<<< orphan*/  wc_id; int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_wc__db_lock_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
struct svn_wc__db_moved_to_info_t {struct svn_wc__db_moved_to_info_t* next; void* shadow_op_root_abspath; void* moved_to_abspath; } ;
struct svn_wc__db_info_t {scalar_t__ status; scalar_t__ kind; int file_external; int moved_here; int incomplete; int special; void* has_descendants; int /*<<< orphan*/  locked; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  copied; int /*<<< orphan*/  has_checksum; scalar_t__ props_mod; scalar_t__ had_props; int /*<<< orphan*/ * lock; void* have_base; struct svn_wc__db_moved_to_info_t* moved_to; scalar_t__ have_more_work; int /*<<< orphan*/  depth; int /*<<< orphan*/  changed_author; int /*<<< orphan*/  changed_date; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  repos_relpath; int /*<<< orphan*/  revnum; int /*<<< orphan*/  op_root; int /*<<< orphan*/  conflicted; int /*<<< orphan*/  changelist; int /*<<< orphan*/  recorded_time; int /*<<< orphan*/  recorded_size; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  STMT_SELECT_MOVED_TO_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_SPECIAL ; 
 void* TRUE ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  db_read_pristine_props (int /*<<< orphan*/ **,TYPE_1__*,char const*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_conflict_descendants (void**,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_wclocked (int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,void**,scalar_t__*,scalar_t__*,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_addition (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 char* svn_relpath_prefix (char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*) ; 
 int svn_sqlite__column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* svn_sqlite__column_text (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info_internal (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*,int /*<<< orphan*/ **,scalar_t__*,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_fetch_repos_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_props_internal (int /*<<< orphan*/ **,TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_moved_here ; 

__attribute__((used)) static svn_error_t *
read_single_info(const struct svn_wc__db_info_t **info,
                 svn_wc__db_wcroot_t *wcroot,
                 const char *local_relpath,
                 svn_boolean_t base_tree_only,
                 apr_pool_t *result_pool,
                 apr_pool_t *scratch_pool)
{
  struct svn_wc__db_info_t *mtb;
  apr_int64_t repos_id;
  const svn_checksum_t *checksum;
  const char *original_repos_relpath;
  svn_boolean_t have_work;
  apr_hash_t *properties;

  mtb = apr_pcalloc(result_pool, sizeof(*mtb));

  if (!base_tree_only)
    SVN_ERR(read_info(&mtb->status, &mtb->kind, &mtb->revnum,
                      &mtb->repos_relpath, &repos_id, &mtb->changed_rev,
                      &mtb->changed_date, &mtb->changed_author, &mtb->depth,
                      &checksum, NULL, &original_repos_relpath, NULL, NULL,
                      &mtb->lock, &mtb->recorded_size, &mtb->recorded_time,
                      &mtb->changelist, &mtb->conflicted, &mtb->op_root,
                      &mtb->had_props, &mtb->props_mod, &mtb->have_base,
                      &mtb->have_more_work, &have_work,
                      wcroot, local_relpath, result_pool, scratch_pool));
  else
    {
      svn_boolean_t update_root;

      have_work = FALSE;
      original_repos_relpath = NULL;

      SVN_ERR(svn_wc__db_base_get_info_internal(
                  &mtb->status, &mtb->kind, &mtb->revnum, &mtb->repos_relpath,
                  &repos_id, &mtb->changed_rev, &mtb->changed_date,
                  &mtb->changed_author, &mtb->depth, &checksum, NULL,
                  &mtb->lock, &mtb->had_props, &properties, &update_root,
                  wcroot, local_relpath, scratch_pool, scratch_pool));

      mtb->have_base = TRUE;
      mtb->file_external = (update_root && mtb->kind == svn_node_file);
    }

  /* Query the same rows in the database again for move information */
  if (have_work && (mtb->have_base || mtb->have_more_work))
    {
      svn_sqlite__stmt_t *stmt;
      svn_boolean_t have_row;

      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_MOVED_TO_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));

      SVN_ERR(svn_sqlite__step(&have_row, stmt));

      while (have_row)
        {
          struct svn_wc__db_moved_to_info_t *move;
          int op_depth = svn_sqlite__column_int(stmt, 0);
          const char *moved_to_relpath = svn_sqlite__column_text(stmt, 1, NULL);
          const char *cur_relpath;

          move = apr_pcalloc(result_pool, sizeof(*move));
          move->moved_to_abspath = svn_dirent_join(wcroot->abspath,
                                                   moved_to_relpath,
                                                   result_pool);

          cur_relpath = svn_relpath_prefix(local_relpath, op_depth,
                                           scratch_pool);

          move->shadow_op_root_abspath = svn_dirent_join(wcroot->abspath,
                                                         cur_relpath,
                                                         result_pool);

          move->next = mtb->moved_to;
          mtb->moved_to = move;

          SVN_ERR(svn_sqlite__step(&have_row, stmt));
        }

      SVN_ERR(svn_sqlite__reset(stmt));
    }

  /* Maybe we have to get some shadowed lock from BASE to make our test suite
     happy... (It might be completely unrelated, but...)
     This queries the same BASE row again, joined to the lock table */
  if (!base_tree_only && mtb->have_base
      && (have_work || mtb->kind == svn_node_file))
    {
      svn_boolean_t update_root;
      svn_wc__db_lock_t **lock_arg = NULL;

      if (have_work)
        lock_arg = &mtb->lock;

      SVN_ERR(svn_wc__db_base_get_info_internal(NULL, NULL, NULL, NULL, NULL,
                                                NULL, NULL, NULL, NULL, NULL,
                                                NULL, lock_arg, NULL, NULL,
                                                &update_root,
                                                wcroot, local_relpath,
                                                result_pool, scratch_pool));

      mtb->file_external = (update_root && mtb->kind == svn_node_file);
    }

  if (mtb->status == svn_wc__db_status_added)
    {
      svn_wc__db_status_t status;

      SVN_ERR(scan_addition(&status, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                            NULL, NULL,
                            wcroot, local_relpath,
                            result_pool, scratch_pool));

      mtb->moved_here = (status == svn_wc__db_status_moved_here);
      mtb->incomplete = (status == svn_wc__db_status_incomplete);
    }

#ifdef HAVE_SYMLINK
  if (mtb->kind == svn_node_file
      && (mtb->had_props || mtb->props_mod
          || (base_tree_only && properties)))
    {
      if (!base_tree_only)
        {
          if (mtb->props_mod)
            SVN_ERR(svn_wc__db_read_props_internal(&properties,
                                                   wcroot, local_relpath,
                                                   scratch_pool, scratch_pool));
          else
            SVN_ERR(db_read_pristine_props(&properties, wcroot, local_relpath,
                                           TRUE /* deleted_ok */,
                                           scratch_pool, scratch_pool));
        }

      mtb->special = (NULL != svn_hash_gets(properties, SVN_PROP_SPECIAL));
    }
#endif

  mtb->has_checksum = (checksum != NULL);
  mtb->copied = (original_repos_relpath != NULL);

  SVN_ERR(svn_wc__db_fetch_repos_info(&mtb->repos_root_url, &mtb->repos_uuid,
                                      wcroot, repos_id, result_pool));

  if (!base_tree_only && mtb->kind == svn_node_dir)
    SVN_ERR(is_wclocked(&mtb->locked, wcroot, local_relpath, scratch_pool));

  if (mtb->kind == svn_node_dir)
    mtb->has_descendants = TRUE;
  else
    SVN_ERR(find_conflict_descendants(&mtb->has_descendants,
                                      wcroot, local_relpath, scratch_pool));

  *info = mtb;

  return SVN_NO_ERROR;
}