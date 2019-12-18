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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_prop_retrieve_recursive (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__prop_retrieve_recursive(apr_hash_t **values,
                                svn_wc_context_t *wc_ctx,
                                const char *local_abspath,
                                const char *propname,
                                apr_pool_t *result_pool,
                                apr_pool_t *scratch_pool)
{
  return svn_error_trace(
            svn_wc__db_prop_retrieve_recursive(values,
                                               wc_ctx->db,
                                               local_abspath,
                                               propname,
                                               result_pool, scratch_pool));
}