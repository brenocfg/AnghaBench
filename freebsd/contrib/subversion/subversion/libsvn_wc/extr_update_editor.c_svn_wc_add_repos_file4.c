#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_wc__db_install_data_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_26__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (char const*) ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_EXISTS ; 
 int /*<<< orphan*/  SVN_ERR_ENTRY_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNEXPECTED_KIND ; 
 int /*<<< orphan*/  SVN_ERR_UNSUPPORTED_FEATURE ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_SCHEDULE_CONFLICT ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* accumulate_last_change (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_categorize_props (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_createf (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,char const*,...) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_io_file_del_none ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/ * svn_prop_array_to_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_hash_to_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_copy3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_stream_open_unique (int /*<<< orphan*/ **,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* svn_uri_skip_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_op_copy_file (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_pristine_install (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_pristine_prepare_install (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_read_info (int*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__db_scan_addition (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
#define  svn_wc__db_status_added 131 
#define  svn_wc__db_status_deleted 130 
#define  svn_wc__db_status_normal 129 
#define  svn_wc__db_status_not_present 128 
 TYPE_2__* svn_wc__db_temp_wcroot_tempdir (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__wq_build_file_install (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__wq_build_file_remove (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc__wq_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__wq_run (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc__write_check (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_add_repos_file4(svn_wc_context_t *wc_ctx,
                       const char *local_abspath,
                       svn_stream_t *new_base_contents,
                       svn_stream_t *new_contents,
                       apr_hash_t *new_base_props,
                       apr_hash_t *new_props,
                       const char *copyfrom_url,
                       svn_revnum_t copyfrom_rev,
                       svn_cancel_func_t cancel_func,
                       void *cancel_baton,
                       apr_pool_t *scratch_pool)
{
  svn_wc__db_t *db = wc_ctx->db;
  const char *dir_abspath = svn_dirent_dirname(local_abspath, scratch_pool);
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  const char *tmp_text_base_abspath;
  svn_checksum_t *new_text_base_md5_checksum;
  svn_checksum_t *new_text_base_sha1_checksum;
  const char *source_abspath = NULL;
  svn_skel_t *all_work_items = NULL;
  svn_skel_t *work_item;
  const char *repos_root_url;
  const char *repos_uuid;
  const char *original_repos_relpath;
  svn_revnum_t changed_rev;
  apr_time_t changed_date;
  const char *changed_author;
  svn_stream_t *tmp_base_contents;
  svn_wc__db_install_data_t *install_data;
  svn_error_t *err;
  apr_pool_t *pool = scratch_pool;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));
  SVN_ERR_ASSERT(new_base_contents != NULL);
  SVN_ERR_ASSERT(new_base_props != NULL);

  /* We should have a write lock on this file's parent directory.  */
  SVN_ERR(svn_wc__write_check(db, dir_abspath, pool));

  err = svn_wc__db_read_info(&status, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                             NULL, NULL, NULL,
                             db, local_abspath, scratch_pool, scratch_pool);

  if (err && err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
    return svn_error_trace(err);
  else if(err)
    svn_error_clear(err);
  else
    switch (status)
      {
        case svn_wc__db_status_not_present:
        case svn_wc__db_status_deleted:
          break;
        default:
          return svn_error_createf(SVN_ERR_ENTRY_EXISTS, NULL,
                                   _("Node '%s' exists."),
                                   svn_dirent_local_style(local_abspath,
                                                          scratch_pool));
      }

  SVN_ERR(svn_wc__db_read_info(&status, &kind, NULL, NULL, &repos_root_url,
                               &repos_uuid, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               db, dir_abspath, scratch_pool, scratch_pool));

  switch (status)
    {
      case svn_wc__db_status_normal:
      case svn_wc__db_status_added:
        break;
      case svn_wc__db_status_deleted:
        return
          svn_error_createf(SVN_ERR_WC_SCHEDULE_CONFLICT, NULL,
                            _("Can't add '%s' to a parent directory"
                              " scheduled for deletion"),
                            svn_dirent_local_style(local_abspath,
                                                   scratch_pool));
      default:
        return svn_error_createf(SVN_ERR_ENTRY_NOT_FOUND, err,
                                 _("Can't find parent directory's node while"
                                   " trying to add '%s'"),
                                 svn_dirent_local_style(local_abspath,
                                                        scratch_pool));
    }
  if (kind != svn_node_dir)
    return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                             _("Can't schedule an addition of '%s'"
                               " below a not-directory node"),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));

  /* Fabricate the anticipated new URL of the target and check the
     copyfrom URL to be in the same repository. */
  if (copyfrom_url != NULL)
    {
      /* Find the repository_root via the parent directory, which
         is always versioned before this function is called */

      if (!repos_root_url)
        {
          /* The parent is an addition, scan upwards to find the right info */
          SVN_ERR(svn_wc__db_scan_addition(NULL, NULL, NULL,
                                           &repos_root_url, &repos_uuid,
                                           NULL, NULL, NULL, NULL,
                                           wc_ctx->db, dir_abspath,
                                           scratch_pool, scratch_pool));
        }
      SVN_ERR_ASSERT(repos_root_url);

      original_repos_relpath =
          svn_uri_skip_ancestor(repos_root_url, copyfrom_url, scratch_pool);

      if (!original_repos_relpath)
        return svn_error_createf(SVN_ERR_UNSUPPORTED_FEATURE, NULL,
                                 _("Copyfrom-url '%s' has different repository"
                                   " root than '%s'"),
                                 copyfrom_url, repos_root_url);
    }
  else
    {
      original_repos_relpath = NULL;
      copyfrom_rev = SVN_INVALID_REVNUM;  /* Just to be sure.  */
    }

  /* Set CHANGED_* to reflect the entry props in NEW_BASE_PROPS, and
     filter NEW_BASE_PROPS so it contains only regular props. */
  {
    apr_array_header_t *regular_props;
    apr_array_header_t *entry_props;

    SVN_ERR(svn_categorize_props(svn_prop_hash_to_array(new_base_props, pool),
                                 &entry_props, NULL, &regular_props,
                                 pool));

    /* Put regular props back into a hash table. */
    new_base_props = svn_prop_array_to_hash(regular_props, pool);

    /* Get the change_* info from the entry props.  */
    SVN_ERR(accumulate_last_change(&changed_rev,
                                   &changed_date,
                                   &changed_author,
                                   entry_props, pool, pool));
  }

  /* Copy NEW_BASE_CONTENTS into a temporary file so our log can refer to
     it, and set TMP_TEXT_BASE_ABSPATH to its path.  Compute its
     NEW_TEXT_BASE_MD5_CHECKSUM and NEW_TEXT_BASE_SHA1_CHECKSUM as we copy. */
  if (copyfrom_url)
    {
      SVN_ERR(svn_wc__db_pristine_prepare_install(&tmp_base_contents,
                                                  &install_data,
                                                  &new_text_base_sha1_checksum,
                                                  &new_text_base_md5_checksum,
                                                  wc_ctx->db, local_abspath,
                                                  scratch_pool, scratch_pool));
    }
  else
    {
      const char *tmp_dir_abspath;

      /* We are not installing a PRISTINE file, but we use the same code to
         create whatever we want to install */

      SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&tmp_dir_abspath,
                                             db, dir_abspath,
                                             scratch_pool, scratch_pool));

      SVN_ERR(svn_stream_open_unique(&tmp_base_contents, &tmp_text_base_abspath,
                                     tmp_dir_abspath, svn_io_file_del_none,
                                     scratch_pool, scratch_pool));

      new_text_base_sha1_checksum = NULL;
      new_text_base_md5_checksum = NULL;
    }
  SVN_ERR(svn_stream_copy3(new_base_contents, tmp_base_contents,
                           cancel_func, cancel_baton, pool));

  /* If the caller gave us a new working file, copy it to a safe (temporary)
     location and set SOURCE_ABSPATH to that path. We'll then translate/copy
     that into place after the node's state has been created.  */
  if (new_contents)
    {
      const char *temp_dir_abspath;
      svn_stream_t *tmp_contents;

      SVN_ERR(svn_wc__db_temp_wcroot_tempdir(&temp_dir_abspath, db,
                                             local_abspath, pool, pool));
      SVN_ERR(svn_stream_open_unique(&tmp_contents, &source_abspath,
                                     temp_dir_abspath, svn_io_file_del_none,
                                     pool, pool));
      SVN_ERR(svn_stream_copy3(new_contents, tmp_contents,
                               cancel_func, cancel_baton, pool));
    }

  /* Install new text base for copied files. Added files do NOT have a
     text base.  */
  if (copyfrom_url != NULL)
    {
      SVN_ERR(svn_wc__db_pristine_install(install_data,
                                          new_text_base_sha1_checksum,
                                          new_text_base_md5_checksum, pool));
    }
  else
    {
      /* ### There's something wrong around here.  Sometimes (merge from a
         foreign repository, at least) we are called with copyfrom_url =
         NULL and an empty new_base_contents (and an empty set of
         new_base_props).  Why an empty "new base"?

         That happens in merge_tests.py 54,87,88,89,143.

         In that case, having been given this supposed "new base" file, we
         copy it and calculate its checksum but do not install it.  Why?
         That must be wrong.

         To crudely work around one issue with this, that we shouldn't
         record a checksum in the database if we haven't installed the
         corresponding pristine text, for now we'll just set the checksum
         to NULL.

         The proper solution is probably more like: the caller should pass
         NULL for the missing information, and this function should learn to
         handle that. */

      new_text_base_sha1_checksum = NULL;
      new_text_base_md5_checksum = NULL;
    }

  /* For added files without NEW_CONTENTS, then generate the working file
     from the provided "pristine" contents.  */
  if (new_contents == NULL && copyfrom_url == NULL)
    source_abspath = tmp_text_base_abspath;

  {
    svn_boolean_t record_fileinfo;

    /* If new contents were provided, then we do NOT want to record the
       file information. We assume the new contents do not match the
       "proper" values for RECORDED_SIZE and RECORDED_TIME.  */
    record_fileinfo = (new_contents == NULL);

    /* Install the working copy file (with appropriate translation) from
       the appropriate source. SOURCE_ABSPATH will be NULL, indicating an
       installation from the pristine (available for copied/moved files),
       or it will specify a temporary file where we placed a "pristine"
       (for an added file) or a detranslated local-mods file.  */
    SVN_ERR(svn_wc__wq_build_file_install(&work_item,
                                          db, local_abspath,
                                          source_abspath,
                                          FALSE /* use_commit_times */,
                                          record_fileinfo,
                                          pool, pool));
    all_work_items = svn_wc__wq_merge(all_work_items, work_item, pool);

    /* If we installed from somewhere besides the official pristine, then
       it is a temporary file, which needs to be removed.  */
    if (source_abspath != NULL)
      {
        SVN_ERR(svn_wc__wq_build_file_remove(&work_item, db, local_abspath,
                                             source_abspath,
                                             pool, pool));
        all_work_items = svn_wc__wq_merge(all_work_items, work_item, pool);
      }
  }

  SVN_ERR(svn_wc__db_op_copy_file(db, local_abspath,
                                  new_base_props,
                                  changed_rev,
                                  changed_date,
                                  changed_author,
                                  original_repos_relpath,
                                  original_repos_relpath ? repos_root_url
                                                         : NULL,
                                  original_repos_relpath ? repos_uuid : NULL,
                                  copyfrom_rev,
                                  new_text_base_sha1_checksum,
                                  TRUE,
                                  new_props,
                                  FALSE /* is_move */,
                                  NULL /* conflict */,
                                  all_work_items,
                                  pool));

  return svn_error_trace(svn_wc__wq_run(db, dir_abspath,
                                        cancel_func, cancel_baton,
                                        pool));
}