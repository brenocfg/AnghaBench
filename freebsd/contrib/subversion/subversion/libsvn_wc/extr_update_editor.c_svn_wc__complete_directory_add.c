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
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_COPYFROM_PATH_NOT_FOUND ; 
 int /*<<< orphan*/  SVN_ERR_WC_PATH_UNEXPECTED_STATUS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  accumulate_last_change (scalar_t__*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_categorize_props (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_prop_array_to_hash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_prop_hash_to_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_op_copy_dir (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,char const*,char const*,char const*,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,char const**,char const**,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 

svn_error_t *
svn_wc__complete_directory_add(svn_wc_context_t *wc_ctx,
                               const char *local_abspath,
                               apr_hash_t *new_original_props,
                               const char *copyfrom_url,
                               svn_revnum_t copyfrom_rev,
                               apr_pool_t *scratch_pool)
{
  svn_wc__db_status_t status;
  svn_node_kind_t kind;
  const char *original_repos_relpath;
  const char *original_root_url;
  const char *original_uuid;
  svn_boolean_t had_props;
  svn_boolean_t props_mod;

  svn_revnum_t original_revision;
  svn_revnum_t changed_rev;
  apr_time_t changed_date;
  const char *changed_author;

  SVN_ERR(svn_wc__db_read_info(&status, &kind, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL,
                               &original_repos_relpath, &original_root_url,
                               &original_uuid, &original_revision, NULL, NULL,
                               NULL, NULL, NULL, NULL, &had_props, &props_mod,
                               NULL, NULL, NULL,
                               wc_ctx->db, local_abspath,
                               scratch_pool, scratch_pool));

  if (status != svn_wc__db_status_added
      || kind != svn_node_dir
      || had_props
      || props_mod
      || !original_repos_relpath)
    {
      return svn_error_createf(
                    SVN_ERR_WC_PATH_UNEXPECTED_STATUS, NULL,
                    _("'%s' is not an unmodified copied directory"),
                    svn_dirent_local_style(local_abspath, scratch_pool));
    }
  if (original_revision != copyfrom_rev
      || strcmp(copyfrom_url,
                 svn_path_url_add_component2(original_root_url,
                                             original_repos_relpath,
                                             scratch_pool)))
    {
      return svn_error_createf(
                    SVN_ERR_WC_COPYFROM_PATH_NOT_FOUND, NULL,
                    _("Copyfrom '%s' doesn't match original location of '%s'"),
                    copyfrom_url,
                    svn_dirent_local_style(local_abspath, scratch_pool));
    }

  {
    apr_array_header_t *regular_props;
    apr_array_header_t *entry_props;

    SVN_ERR(svn_categorize_props(svn_prop_hash_to_array(new_original_props,
                                                        scratch_pool),
                                 &entry_props, NULL, &regular_props,
                                 scratch_pool));

    /* Put regular props back into a hash table. */
    new_original_props = svn_prop_array_to_hash(regular_props, scratch_pool);

    /* Get the change_* info from the entry props.  */
    SVN_ERR(accumulate_last_change(&changed_rev,
                                   &changed_date,
                                   &changed_author,
                                   entry_props, scratch_pool, scratch_pool));
  }

  return svn_error_trace(
            svn_wc__db_op_copy_dir(wc_ctx->db, local_abspath,
                                   new_original_props,
                                   changed_rev, changed_date, changed_author,
                                   original_repos_relpath, original_root_url,
                                   original_uuid, original_revision,
                                   NULL /* children */,
                                   svn_depth_infinity,
                                   FALSE /* is_move */,
                                   NULL /* conflict */,
                                   NULL /* work_items */,
                                   scratch_pool));
}