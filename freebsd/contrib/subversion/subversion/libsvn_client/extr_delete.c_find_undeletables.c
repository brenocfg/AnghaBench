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
struct TYPE_3__ {scalar_t__ node_status; scalar_t__ text_status; scalar_t__ prop_status; int /*<<< orphan*/  versioned; } ;
typedef  TYPE_1__ svn_wc_status3_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct can_delete_baton_t {int /*<<< orphan*/  target_missing; int /*<<< orphan*/  root_abspath; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CLIENT_MODIFIED ; 
 int /*<<< orphan*/  SVN_ERR_NODE_UNEXPECTED_KIND ; 
 int /*<<< orphan*/  SVN_ERR_UNVERSIONED_RESOURCE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_wc_status_added ; 
 scalar_t__ svn_wc_status_deleted ; 
 scalar_t__ svn_wc_status_missing ; 
 scalar_t__ svn_wc_status_none ; 
 scalar_t__ svn_wc_status_normal ; 
 scalar_t__ svn_wc_status_obstructed ; 
 scalar_t__ svn_wc_status_replaced ; 

__attribute__((used)) static svn_error_t *
find_undeletables(void *baton,
                  const char *local_abspath,
                  const svn_wc_status3_t *status,
                  apr_pool_t *pool)
{
  if (status->node_status == svn_wc_status_missing)
    {
      struct can_delete_baton_t *cdt = baton;

      if (strcmp(cdt->root_abspath, local_abspath) == 0)
        cdt->target_missing = TRUE;
    }

  /* Check for error-ful states. */
  if (status->node_status == svn_wc_status_obstructed)
    return svn_error_createf(SVN_ERR_NODE_UNEXPECTED_KIND, NULL,
                             _("'%s' is in the way of the resource "
                               "actually under version control"),
                             svn_dirent_local_style(local_abspath, pool));
  else if (! status->versioned)
    return svn_error_createf(SVN_ERR_UNVERSIONED_RESOURCE, NULL,
                             _("'%s' is not under version control"),
                             svn_dirent_local_style(local_abspath, pool));
  else if ((status->node_status == svn_wc_status_added
            || status->node_status == svn_wc_status_replaced)
           && status->text_status == svn_wc_status_normal
           && (status->prop_status == svn_wc_status_normal
               || status->prop_status == svn_wc_status_none))
    {
      /* Unmodified copy. Go ahead, remove it */
    }
  else if (status->node_status != svn_wc_status_normal
           && status->node_status != svn_wc_status_deleted
           && status->node_status != svn_wc_status_missing)
    return svn_error_createf(SVN_ERR_CLIENT_MODIFIED, NULL,
                             _("'%s' has local modifications -- commit or "
                               "revert them first"),
                             svn_dirent_local_style(local_abspath, pool));

  return SVN_NO_ERROR;
}