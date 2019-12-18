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
typedef  scalar_t__ svn_wc__db_status_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_time_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc__db_base_get_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_pristine_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc__db_status_added ; 
 scalar_t__ svn_wc__db_status_deleted ; 

svn_error_t *
svn_wc__node_get_pre_ng_status_data(svn_revnum_t *revision,
                                   svn_revnum_t *changed_rev,
                                   apr_time_t *changed_date,
                                   const char **changed_author,
                                   svn_wc_context_t *wc_ctx,
                                   const char *local_abspath,
                                   apr_pool_t *result_pool,
                                   apr_pool_t *scratch_pool)
{
  svn_wc__db_status_t status;
  svn_boolean_t have_base, have_more_work, have_work;

  SVN_ERR(svn_wc__db_read_info(&status, NULL, revision, NULL, NULL, NULL,
                               changed_rev, changed_date, changed_author,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               NULL, NULL, NULL, NULL, NULL, NULL, NULL,
                               &have_base, &have_more_work, &have_work,
                               wc_ctx->db, local_abspath,
                               result_pool, scratch_pool));

  if (!have_work
      || ((!changed_rev || SVN_IS_VALID_REVNUM(*changed_rev))
          && (!revision || SVN_IS_VALID_REVNUM(*revision)))
      || ((status != svn_wc__db_status_added)
          && (status != svn_wc__db_status_deleted)))
    {
      return SVN_NO_ERROR; /* We got everything we need */
    }

  if (have_base && !have_more_work)
    SVN_ERR(svn_wc__db_base_get_info(NULL, NULL, revision, NULL, NULL, NULL,
                                     changed_rev, changed_date, changed_author,
                                     NULL, NULL, NULL,
                                     NULL, NULL, NULL, NULL,
                                     wc_ctx->db, local_abspath,
                                     result_pool, scratch_pool));
  else if (status == svn_wc__db_status_deleted)
    /* Check the information below a WORKING delete */
    SVN_ERR(svn_wc__db_read_pristine_info(NULL, NULL, changed_rev,
                                          changed_date, changed_author, NULL,
                                          NULL, NULL, NULL, NULL,
                                          wc_ctx->db, local_abspath,
                                          result_pool, scratch_pool));

  return SVN_NO_ERROR;
}