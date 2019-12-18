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
struct TYPE_3__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CLIENT_BAD_REVISION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_opt_revision_date ; 
 scalar_t__ svn_opt_revision_head ; 
 scalar_t__ svn_opt_revision_number ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 

__attribute__((used)) static svn_error_t *
ensure_wc_path_has_repo_revision(const char *path_or_url,
                                 const svn_opt_revision_t *revision,
                                 apr_pool_t *scratch_pool)
{
  if (revision->kind != svn_opt_revision_number
      && revision->kind != svn_opt_revision_date
      && revision->kind != svn_opt_revision_head
      && ! svn_path_is_url(path_or_url))
    return svn_error_createf(
      SVN_ERR_CLIENT_BAD_REVISION, NULL,
      _("Invalid merge source '%s'; a working copy path can only be "
        "used with a repository revision (a number, a date, or head)"),
      svn_dirent_local_style(path_or_url, scratch_pool));
  return SVN_NO_ERROR;
}