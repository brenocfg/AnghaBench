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
struct TYPE_3__ {scalar_t__ kind; scalar_t__ text_status; scalar_t__ versioned; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_WC_LEFT_LOCAL_MOD ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_file ; 
 scalar_t__ svn_wc_status_conflicted ; 
 scalar_t__ svn_wc_status_modified ; 

__attribute__((used)) static svn_error_t *
remove_from_revision_status_callback(void *baton,
                                     const char *local_abspath,
                                     const svn_wc_status3_t *status,
                                     apr_pool_t *scratch_pool)
{
  /* For legacy reasons we only check the file contents for changes */
  if (status->versioned
      && status->kind == svn_node_file
      && (status->text_status == svn_wc_status_modified
          || status->text_status == svn_wc_status_conflicted))
    {
      return svn_error_createf(SVN_ERR_WC_LEFT_LOCAL_MOD, NULL,
                               _("File '%s' has local modifications"),
                               svn_dirent_local_style(local_abspath,
                                                      scratch_pool));
    }
  return SVN_NO_ERROR;
}