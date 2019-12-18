#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* modified; void* switched; void* sparse_checkout; void* max_rev; void* min_rev; } ;
typedef  TYPE_1__ svn_wc_revision_status_t ;
struct TYPE_7__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 void* SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_wc__db_revision_status (void**,void**,void**,void**,void**,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_has_local_mods (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_revision_status2(svn_wc_revision_status_t **result_p,
                        svn_wc_context_t *wc_ctx,
                        const char *local_abspath,
                        const char *trail_url,
                        svn_boolean_t committed,
                        svn_cancel_func_t cancel_func,
                        void *cancel_baton,
                        apr_pool_t *result_pool,
                        apr_pool_t *scratch_pool)
{
  svn_wc_revision_status_t *result = apr_pcalloc(result_pool, sizeof(*result));

  *result_p = result;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(local_abspath));

  /* set result as nil */
  result->min_rev  = SVN_INVALID_REVNUM;
  result->max_rev  = SVN_INVALID_REVNUM;
  result->switched = FALSE;
  result->modified = FALSE;
  result->sparse_checkout = FALSE;

  SVN_ERR(svn_wc__db_revision_status(&result->min_rev, &result->max_rev,
                                     &result->sparse_checkout,
                                     &result->modified,
                                     &result->switched,
                                     wc_ctx->db, local_abspath, trail_url,
                                     committed,
                                     scratch_pool));

  if (!result->modified)
    SVN_ERR(svn_wc__node_has_local_mods(&result->modified, NULL,
                                        wc_ctx->db, local_abspath, TRUE,
                                        cancel_func, cancel_baton,
                                        scratch_pool));

  return SVN_NO_ERROR;
}