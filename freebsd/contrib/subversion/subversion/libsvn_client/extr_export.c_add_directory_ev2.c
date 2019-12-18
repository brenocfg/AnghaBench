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
struct TYPE_4__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int /*<<< orphan*/  notify_baton; int /*<<< orphan*/  (* notify_func ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  externals; scalar_t__ force; int /*<<< orphan*/  root_path; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_OS_DEFAULT ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_NOT_WORKING_COPY ; 
 int /*<<< orphan*/  SVN_ERR_WC_OBSTRUCTED_UPDATE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EXTERNALS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_externals (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_dir_make (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_node_none ; 
 TYPE_1__* svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_update_add ; 

__attribute__((used)) static svn_error_t *
add_directory_ev2(void *baton,
                  const char *relpath,
                  const apr_array_header_t *children,
                  apr_hash_t *props,
                  svn_revnum_t replaces_rev,
                  apr_pool_t *scratch_pool)
{
  struct edit_baton *eb = baton;
  svn_node_kind_t kind;
  const char *full_path = svn_dirent_join(eb->root_path, relpath,
                                          scratch_pool);
  svn_string_t *val;

  SVN_ERR(svn_io_check_path(full_path, &kind, scratch_pool));
  if (kind == svn_node_none)
    SVN_ERR(svn_io_dir_make(full_path, APR_OS_DEFAULT, scratch_pool));
  else if (kind == svn_node_file)
    return svn_error_createf(SVN_ERR_WC_NOT_WORKING_COPY, NULL,
                             _("'%s' exists and is not a directory"),
                             svn_dirent_local_style(full_path, scratch_pool));
  else if (! (kind == svn_node_dir && eb->force))
    return svn_error_createf(SVN_ERR_WC_OBSTRUCTED_UPDATE, NULL,
                             _("'%s' already exists"),
                             svn_dirent_local_style(full_path, scratch_pool));

  if ( (val = svn_hash_gets(props, SVN_PROP_EXTERNALS)) )
    SVN_ERR(add_externals(eb->externals, full_path, val));

  if (eb->notify_func)
    {
      svn_wc_notify_t *notify = svn_wc_create_notify(full_path,
                                                     svn_wc_notify_update_add,
                                                     scratch_pool);
      notify->kind = svn_node_dir;
      (*eb->notify_func)(eb->notify_baton, notify, scratch_pool);
    }

  return SVN_NO_ERROR;
}