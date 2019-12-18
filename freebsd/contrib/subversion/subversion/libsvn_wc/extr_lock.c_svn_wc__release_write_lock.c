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
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc__db_wclock_release (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wq_fetch_next (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__release_write_lock(svn_wc_context_t *wc_ctx,
                           const char *local_abspath,
                           apr_pool_t *scratch_pool)
{
  apr_uint64_t id;
  svn_skel_t *work_item;

  SVN_ERR(svn_wc__db_wq_fetch_next(&id, &work_item, wc_ctx->db, local_abspath,
                                   0, scratch_pool, scratch_pool));
  if (work_item)
    {
      /* Do not release locks (here or below) if there is work to do.  */
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_wc__db_wclock_release(wc_ctx->db, local_abspath, scratch_pool));

  return SVN_NO_ERROR;
}