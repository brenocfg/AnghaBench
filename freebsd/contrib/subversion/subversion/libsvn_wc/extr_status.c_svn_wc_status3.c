#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_wc_status3_t ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
struct TYPE_6__ {int /*<<< orphan*/  s; } ;
typedef  TYPE_2__ svn_wc__internal_status_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  internal_status (TYPE_2__**,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_status3(svn_wc_status3_t **status,
               svn_wc_context_t *wc_ctx,
               const char *local_abspath,
               apr_pool_t *result_pool,
               apr_pool_t *scratch_pool)
{
  svn_wc__internal_status_t *stat;
  SVN_ERR(internal_status(&stat, wc_ctx->db, local_abspath,
                          TRUE /* check_working_copy */,
                          result_pool, scratch_pool));
  *status = &stat->s;
  return SVN_NO_ERROR;
}