#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  (* svn_wc__node_found_func_t ) (char const*,scalar_t__,void*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_4__ {scalar_t__ nelts; } ;
typedef  TYPE_1__ apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNKNOWN_KIND ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  convert_db_kind_to_node_kind (scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_depth_empty ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_from_cstring_keys (int /*<<< orphan*/ **,TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_excluded ; 
 scalar_t__ svn_wc__db_status_not_present ; 
 scalar_t__ svn_wc__db_status_server_excluded ; 
 int /*<<< orphan*/  walker_helper (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (char const*,scalar_t__,void*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__internal_walk_children(svn_wc__db_t *db,
                               const char *local_abspath,
                               svn_boolean_t show_hidden,
                               const apr_array_header_t *changelist_filter,
                               svn_wc__node_found_func_t walk_callback,
                               void *walk_baton,
                               svn_depth_t walk_depth,
                               svn_cancel_func_t cancel_func,
                               void *cancel_baton,
                               apr_pool_t *scratch_pool)
{
  svn_node_kind_t db_kind;
  svn_node_kind_t kind;
  svn_wc__db_status_t status;
  apr_hash_t *changelist_hash = NULL;
  const char *changelist = NULL;

  SVN_ERR_ASSERT(walk_depth >= svn_depth_empty
                 && walk_depth <= svn_depth_infinity);

  if (changelist_filter && changelist_filter->nelts)
    SVN_ERR(svn_hash_from_cstring_keys(&changelist_hash, changelist_filter,
                                       scratch_pool));

  /* Check if the node exists before the first callback */
  SVN_ERR(svn_wc__db_read_info(&status, &db_kind, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               changelist_hash ? &changelist : NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               db, local_abspath, scratch_pool, scratch_pool));

  SVN_ERR(convert_db_kind_to_node_kind(&kind, db_kind, status, show_hidden));

  if (!changelist_hash
      || (changelist && svn_hash_gets(changelist_hash, changelist)))
    {
      SVN_ERR(walk_callback(local_abspath, kind, walk_baton, scratch_pool));
    }

  if (db_kind == svn_node_file
      || status == svn_wc__db_status_not_present
      || status == svn_wc__db_status_excluded
      || status == svn_wc__db_status_server_excluded)
    return SVN_NO_ERROR;

  if (db_kind == svn_node_dir)
    {
      return svn_error_trace(
        walker_helper(db, local_abspath, show_hidden, changelist_hash,
                      walk_callback, walk_baton,
                      walk_depth, cancel_func, cancel_baton, scratch_pool));
    }

  return svn_error_createf(SVN_ERR_NODE_UNKNOWN_KIND, NULL,
                           _("'%s' has an unrecognized node kind"),
                           svn_dirent_local_style(local_abspath,
                                                  scratch_pool));
}