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
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_6__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
struct TYPE_7__ {int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  url; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  rev; } ;
typedef  TYPE_2__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_origin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__wc_node_get_origin(svn_client__pathrev_t **origin_p,
                               const char *wc_abspath,
                               svn_client_ctx_t *ctx,
                               apr_pool_t *result_pool,
                               apr_pool_t *scratch_pool)
{
  const char *relpath;

  *origin_p = apr_palloc(result_pool, sizeof(**origin_p));

  SVN_ERR(svn_wc__node_get_origin(NULL /* is_copy */,
                                  &(*origin_p)->rev,
                                  &relpath,
                                  &(*origin_p)->repos_root_url,
                                  &(*origin_p)->repos_uuid,
                                  NULL, NULL,
                                  ctx->wc_ctx, wc_abspath,
                                  FALSE /* scan_deleted */,
                                  result_pool, scratch_pool));
  if ((*origin_p)->repos_root_url && relpath)
    {
      (*origin_p)->url = svn_path_url_add_component2(
                           (*origin_p)->repos_root_url, relpath, result_pool);
    }
  else
    {
      *origin_p = NULL;
    }
  return SVN_NO_ERROR;
}