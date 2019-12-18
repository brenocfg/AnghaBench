#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_client__pathrev_t ;
struct TYPE_4__ {int /*<<< orphan*/  tip; } ;
struct TYPE_5__ {int /*<<< orphan*/  source_ra_session; TYPE_1__ target_branch; int /*<<< orphan*/  source_branch; int /*<<< orphan*/  yca; } ;
typedef  TYPE_2__ source_and_target_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  find_last_merged_location (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_base_on_source(svn_client__pathrev_t **base_p,
                    source_and_target_t *s_t,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *result_pool,
                    apr_pool_t *scratch_pool)
{
  SVN_ERR(find_last_merged_location(base_p,
                                    s_t->yca,
                                    &s_t->source_branch,
                                    s_t->target_branch.tip,
                                    ctx,
                                    s_t->source_ra_session,
                                    result_pool, scratch_pool));
  return SVN_NO_ERROR;
}