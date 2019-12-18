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
struct TYPE_4__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct edit_baton {int /*<<< orphan*/  wcroot_abspath; int /*<<< orphan*/  db; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_SUCCESS ; 
 int /*<<< orphan*/ * apr_pool_parent_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_wc__wq_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static apr_status_t
cleanup_edit_baton(void *edit_baton)
{
  struct edit_baton *eb = edit_baton;
  svn_error_t *err;
  apr_pool_t *pool = apr_pool_parent_get(eb->pool);

  err = svn_wc__wq_run(eb->db, eb->wcroot_abspath,
                       NULL /* cancel_func */, NULL /* cancel_baton */,
                       pool);

  if (err)
    {
      apr_status_t apr_err = err->apr_err;
      svn_error_clear(err);
      return apr_err;
    }
  return APR_SUCCESS;
}