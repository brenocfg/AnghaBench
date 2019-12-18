#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_lock_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct file_baton {int /*<<< orphan*/  local_abspath; TYPE_2__* edit_baton; scalar_t__ prop_changed; scalar_t__ text_changed; int /*<<< orphan*/  name; int /*<<< orphan*/  dir_baton; scalar_t__ added; } ;
typedef  enum svn_wc_status_kind { ____Placeholder_svn_wc_status_kind } svn_wc_status_kind ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_3__ {int /*<<< orphan*/  check_working_copy; scalar_t__ repos_locks; } ;
struct TYPE_4__ {TYPE_1__ wb; int /*<<< orphan*/  db; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* find_dir_repos_relpath (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fspath__join (char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_hash_gets (scalar_t__,int /*<<< orphan*/ ) ; 
 char* svn_relpath_join (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int svn_wc_status_added ; 
 int svn_wc_status_modified ; 
 int /*<<< orphan*/ * tweak_statushash (struct file_baton*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_file(void *file_baton,
           const char *text_checksum,  /* ignored, as we receive no data */
           apr_pool_t *pool)
{
  struct file_baton *fb = file_baton;
  enum svn_wc_status_kind repos_node_status;
  enum svn_wc_status_kind repos_text_status;
  enum svn_wc_status_kind repos_prop_status;
  const svn_lock_t *repos_lock = NULL;

  /* If nothing has changed, return. */
  if (! (fb->added || fb->prop_changed || fb->text_changed))
    return SVN_NO_ERROR;

  /* If this is a new file, add it to the statushash. */
  if (fb->added)
    {
      repos_node_status = svn_wc_status_added;
      repos_text_status = fb->text_changed ? svn_wc_status_modified
                                           : 0 /* don't tweak */;
      repos_prop_status = fb->prop_changed ? svn_wc_status_modified
                                           : 0 /* don't tweak */;

      if (fb->edit_baton->wb.repos_locks)
        {
          const char *dir_repos_relpath = find_dir_repos_relpath(fb->dir_baton,
                                                                 pool);

          /* repos_lock still uses the deprecated filesystem absolute path
             format */
          const char *repos_relpath = svn_relpath_join(dir_repos_relpath,
                                                       fb->name, pool);

          repos_lock = svn_hash_gets(fb->edit_baton->wb.repos_locks,
                                     svn_fspath__join("/", repos_relpath,
                                                      pool));
        }
    }
  else
    {
      repos_node_status = (fb->text_changed || fb->prop_changed)
                                 ? svn_wc_status_modified
                                 : 0 /* don't tweak */;
      repos_text_status = fb->text_changed ? svn_wc_status_modified
                                           : 0 /* don't tweak */;
      repos_prop_status = fb->prop_changed ? svn_wc_status_modified
                                           : 0 /* don't tweak */;
    }

  return tweak_statushash(fb, NULL, FALSE, fb->edit_baton->db,
                          fb->edit_baton->wb.check_working_copy,
                          fb->local_abspath, repos_node_status,
                          repos_text_status, repos_prop_status,
                          SVN_INVALID_REVNUM, repos_lock, pool);
}