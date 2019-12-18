#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
struct edit_baton {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/  cancel_func; int /*<<< orphan*/  status_baton; int /*<<< orphan*/  status_func; int /*<<< orphan*/  ignores; int /*<<< orphan*/  no_ignore; int /*<<< orphan*/  get_all; int /*<<< orphan*/  default_depth; int /*<<< orphan*/  target_abspath; int /*<<< orphan*/  db; scalar_t__ root_opened; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc__internal_walk_status (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
close_edit(void *edit_baton,
           apr_pool_t *pool)
{
  struct edit_baton *eb = edit_baton;

  /* If we get here and the root was not opened as part of the edit,
     we need to transmit statuses for everything.  Otherwise, we
     should be done. */
  if (eb->root_opened)
    return SVN_NO_ERROR;

  SVN_ERR(svn_wc__internal_walk_status(eb->db,
                                       eb->target_abspath,
                                       eb->default_depth,
                                       eb->get_all,
                                       eb->no_ignore,
                                       FALSE,
                                       eb->ignores,
                                       eb->status_func,
                                       eb->status_baton,
                                       eb->cancel_func,
                                       eb->cancel_baton,
                                       pool));

  return SVN_NO_ERROR;
}