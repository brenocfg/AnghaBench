#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  wc_id; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  scalar_t__ svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;
struct TYPE_13__ {scalar_t__ repos_id; scalar_t__ status; scalar_t__ kind; scalar_t__ conflict; int /*<<< orphan*/  work_items; scalar_t__ insert_base_deleted; scalar_t__ delete_working; scalar_t__ file_external; int /*<<< orphan*/  children; int /*<<< orphan*/  revision; int /*<<< orphan*/ * repos_relpath; scalar_t__ new_actual_props; int /*<<< orphan*/ * props; scalar_t__ update_actual_props; int /*<<< orphan*/ * dav_cache; int /*<<< orphan*/  iprops; int /*<<< orphan*/  checksum; int /*<<< orphan*/ * target; int /*<<< orphan*/  changed_author; int /*<<< orphan*/  changed_date; int /*<<< orphan*/  changed_rev; int /*<<< orphan*/  depth; scalar_t__ keep_recorded_info; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  repos_root_url; } ;
typedef  TYPE_2__ insert_base_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int64_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_14__ {scalar_t__ nelts; } ;
typedef  TYPE_3__ apr_array_header_t ;

/* Variables and functions */
 scalar_t__ INVALID_REPOS_ID ; 
 int /*<<< orphan*/  STMT_DELETE_WORKING_NODE ; 
 int /*<<< orphan*/  STMT_INSERT_DELETE_FROM_BASE ; 
 int /*<<< orphan*/  STMT_INSERT_NODE ; 
 int /*<<< orphan*/  STMT_SELECT_BASE_NODE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 scalar_t__ SVN_INVALID_FILESIZE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_work_items (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  create_repos_id (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_extend_parent_delete (TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_retract_parent_delete (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  depth_map ; 
 scalar_t__ get_recorded_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  insert_incomplete_children (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kind_map ; 
 int /*<<< orphan*/  path_for_error_message (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  presence_map ; 
 int /*<<< orphan*/  relpath_depth (char const*) ; 
 int /*<<< orphan*/  set_actual_props (TYPE_1__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_symlink ; 
 int /*<<< orphan*/  svn_prop_diffs (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_relpath_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_checksum (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_int (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  svn_sqlite__bind_int64 (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  svn_sqlite__bind_iprops (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_properties (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bindf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ svn_sqlite__column_int64 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_token__to_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_mark_conflict_internal (TYPE_1__*,char const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_incomplete ; 
 scalar_t__ svn_wc__db_status_normal ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 

__attribute__((used)) static svn_error_t *
insert_base_node(const insert_base_baton_t *pibb,
                 svn_wc__db_wcroot_t *wcroot,
                 const char *local_relpath,
                 apr_pool_t *scratch_pool)
{
  apr_int64_t repos_id = pibb->repos_id;
  svn_sqlite__stmt_t *stmt;
  svn_filesize_t recorded_size = SVN_INVALID_FILESIZE;
  apr_int64_t recorded_time;
  svn_boolean_t present;

  /* The directory at the WCROOT has a NULL parent_relpath. Otherwise,
     bind the appropriate parent_relpath. */
  const char *parent_relpath =
    (*local_relpath == '\0') ? NULL
    : svn_relpath_dirname(local_relpath, scratch_pool);

  if (pibb->repos_id == INVALID_REPOS_ID)
    SVN_ERR(create_repos_id(&repos_id, pibb->repos_root_url, pibb->repos_uuid,
                            wcroot->sdb, scratch_pool));

  SVN_ERR_ASSERT(repos_id != INVALID_REPOS_ID);
  SVN_ERR_ASSERT(pibb->repos_relpath != NULL);

  if (pibb->keep_recorded_info)
    {
      svn_boolean_t have_row;
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_SELECT_BASE_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step(&have_row, stmt));
      if (have_row)
        {
          /* Preserve size and modification time if caller asked us to. */
          recorded_size = get_recorded_size(stmt, 6);
          recorded_time = svn_sqlite__column_int64(stmt, 12);
        }
      SVN_ERR(svn_sqlite__reset(stmt));
    }

  present = (pibb->status == svn_wc__db_status_normal
             || pibb->status == svn_wc__db_status_incomplete);

  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb, STMT_INSERT_NODE));
  SVN_ERR(svn_sqlite__bindf(stmt, "isdsisr"
                            "tstr"               /* 8 - 11 */
                            "isnnnnns",          /* 12 - 19 */
                            wcroot->wc_id,       /* 1 */
                            local_relpath,       /* 2 */
                            0,              /* op_depth is 0 for base */
                            parent_relpath,      /* 4 */
                            repos_id,
                            pibb->repos_relpath,
                            pibb->revision,
                            presence_map, pibb->status, /* 8 */
                            (pibb->kind == svn_node_dir && present) /* 9 */
                              ? svn_token__to_word(depth_map, pibb->depth)
                              : NULL,
                            kind_map, pibb->kind, /* 10 */
                            pibb->changed_rev,    /* 11 */
                            pibb->changed_date,   /* 12 */
                            pibb->changed_author, /* 13 */
                            (pibb->kind == svn_node_symlink && present) ?
                                pibb->target : NULL)); /* 19 */
  if (pibb->kind == svn_node_file && present)
    {
      if (!pibb->checksum
          && pibb->status != svn_wc__db_status_not_present
          && pibb->status != svn_wc__db_status_excluded
          && pibb->status != svn_wc__db_status_server_excluded)
        return svn_error_createf(SVN_ERR_WC_CORRUPT, svn_sqlite__reset(stmt),
                                 _("The file '%s' has no checksum."),
                                 path_for_error_message(wcroot, local_relpath,
                                                        scratch_pool));

      SVN_ERR(svn_sqlite__bind_checksum(stmt, 14, pibb->checksum,
                                        scratch_pool));

      if (recorded_size != SVN_INVALID_FILESIZE)
        {
          SVN_ERR(svn_sqlite__bind_int64(stmt, 16, recorded_size));
          SVN_ERR(svn_sqlite__bind_int64(stmt, 17, recorded_time));
        }
    }

  /* Set properties.  Must be null if presence not normal or incomplete. */
  assert(pibb->status == svn_wc__db_status_normal
         || pibb->status == svn_wc__db_status_incomplete
         || pibb->props == NULL);
  if (present)
    {
      SVN_ERR(svn_sqlite__bind_properties(stmt, 15, pibb->props,
                                          scratch_pool));

      SVN_ERR(svn_sqlite__bind_iprops(stmt, 23, pibb->iprops,
                                      scratch_pool));
    }

  if (pibb->dav_cache)
    SVN_ERR(svn_sqlite__bind_properties(stmt, 18, pibb->dav_cache,
                                        scratch_pool));

  if (pibb->file_external)
    SVN_ERR(svn_sqlite__bind_int(stmt, 20, 1));

  SVN_ERR(svn_sqlite__insert(NULL, stmt));

  if (pibb->update_actual_props)
    {
      /* Cast away const, to allow calling property helpers */
      apr_hash_t *base_props = (apr_hash_t *)pibb->props;
      apr_hash_t *new_actual_props = (apr_hash_t *)pibb->new_actual_props;

      if (base_props != NULL
          && new_actual_props != NULL
          && (apr_hash_count(base_props) == apr_hash_count(new_actual_props)))
        {
          apr_array_header_t *diffs;

          SVN_ERR(svn_prop_diffs(&diffs, new_actual_props, base_props,
                                 scratch_pool));

          if (diffs->nelts == 0)
            new_actual_props = NULL;
        }

      SVN_ERR(set_actual_props(wcroot, local_relpath, new_actual_props,
                               scratch_pool));
    }

  if (pibb->kind == svn_node_dir && pibb->children)
    SVN_ERR(insert_incomplete_children(wcroot->sdb, wcroot->wc_id,
                                       local_relpath,
                                       repos_id,
                                       pibb->repos_relpath,
                                       pibb->revision,
                                       pibb->children,
                                       0 /* BASE */,
                                       scratch_pool));

  /* When this is not the root node, check shadowing behavior */
  if (*local_relpath)
    {
      if (parent_relpath
          && ((pibb->status == svn_wc__db_status_normal)
              || (pibb->status == svn_wc__db_status_incomplete))
          && ! pibb->file_external)
        {
          SVN_ERR(db_extend_parent_delete(wcroot, local_relpath,
                                          pibb->kind, 0,
                                          scratch_pool));
        }
      else if (pibb->status == svn_wc__db_status_not_present
               || pibb->status == svn_wc__db_status_server_excluded
               || pibb->status == svn_wc__db_status_excluded)
        {
          SVN_ERR(db_retract_parent_delete(wcroot, local_relpath, 0,
                                           scratch_pool));
        }
    }

  if (pibb->delete_working)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                    STMT_DELETE_WORKING_NODE));
      SVN_ERR(svn_sqlite__bindf(stmt, "is", wcroot->wc_id, local_relpath));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }
  if (pibb->insert_base_deleted)
    {
      SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb,
                                        STMT_INSERT_DELETE_FROM_BASE));
      SVN_ERR(svn_sqlite__bindf(stmt, "isd",
                                wcroot->wc_id, local_relpath,
                                relpath_depth(local_relpath)));
      SVN_ERR(svn_sqlite__step_done(stmt));
    }

  SVN_ERR(add_work_items(wcroot->sdb, pibb->work_items, scratch_pool));
  if (pibb->conflict)
    SVN_ERR(svn_wc__db_mark_conflict_internal(wcroot, local_relpath,
                                              pibb->conflict, scratch_pool));

  return SVN_NO_ERROR;
}