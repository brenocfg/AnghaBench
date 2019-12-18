#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
struct TYPE_15__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ svn_string_t ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_3__ svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_3__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_EXTERNALS ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ svn_depth_infinity ; 
 int /*<<< orphan*/  svn_depth_to_word (scalar_t__) ; 
 scalar_t__ svn_depth_unknown ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_3__*) ; 
 TYPE_3__* svn_error_trace (TYPE_3__*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 TYPE_3__* svn_wc__db_externals_gather_definitions (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_read_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* svn_wc_prop_get2 (TYPE_2__ const**,TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__externals_gather_definitions(apr_hash_t **externals,
                                     apr_hash_t **depths,
                                     svn_wc_context_t *wc_ctx,
                                     const char *local_abspath,
                                     svn_depth_t depth,
                                     apr_pool_t *result_pool,
                                     apr_pool_t *scratch_pool)
{
  if (depth == svn_depth_infinity
      || depth == svn_depth_unknown)
    {
      return svn_error_trace(
        svn_wc__db_externals_gather_definitions(externals, depths,
                                                wc_ctx->db, local_abspath,
                                                result_pool, scratch_pool));
    }
  else
    {
      const svn_string_t *value;
      svn_error_t *err;
      *externals = apr_hash_make(result_pool);

      local_abspath = apr_pstrdup(result_pool, local_abspath);

      err = svn_wc_prop_get2(&value, wc_ctx, local_abspath,
                             SVN_PROP_EXTERNALS, result_pool, scratch_pool);

      if (err)
        {
          if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
            return svn_error_trace(err);

          svn_error_clear(err);
          value = NULL;
        }

      if (value)
        svn_hash_sets(*externals, local_abspath, value->data);

      if (value && depths)
        {
          svn_depth_t node_depth;
          *depths = apr_hash_make(result_pool);

          SVN_ERR(svn_wc__db_read_info(NULL, NULL, NULL, NULL, NULL, NULL,
                                       NULL, NULL, NULL, &node_depth, NULL,
                                       NULL, NULL, NULL, NULL, NULL, NULL,
                                       NULL, NULL, NULL, NULL, NULL, NULL,
                                       NULL, NULL, NULL, NULL,
                                       wc_ctx->db, local_abspath,
                                       scratch_pool, scratch_pool));

          svn_hash_sets(*depths, local_abspath, svn_depth_to_word(node_depth));
        }

      return SVN_NO_ERROR;
    }
}