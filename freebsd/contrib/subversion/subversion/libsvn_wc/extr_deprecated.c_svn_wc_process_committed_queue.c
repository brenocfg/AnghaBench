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
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_wc_committed_queue_t ;
typedef  int /*<<< orphan*/  svn_wc_adm_access_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_wc__adm_get_db (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__context_create_with_db (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_process_committed_queue2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_process_committed_queue(svn_wc_committed_queue_t *queue,
                               svn_wc_adm_access_t *adm_access,
                               svn_revnum_t new_revnum,
                               const char *rev_date,
                               const char *rev_author,
                               apr_pool_t *pool)
{
  svn_wc_context_t *wc_ctx;

  SVN_ERR(svn_wc__context_create_with_db(&wc_ctx, NULL,
                                         svn_wc__adm_get_db(adm_access),
                                         pool));
  SVN_ERR(svn_wc_process_committed_queue2(queue, wc_ctx, new_revnum,
                                          rev_date, rev_author,
                                          NULL, NULL, pool));
  SVN_ERR(svn_wc_context_destroy(wc_ctx));

  return SVN_NO_ERROR;
}