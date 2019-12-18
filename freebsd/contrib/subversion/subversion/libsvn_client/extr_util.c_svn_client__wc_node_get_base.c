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
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  repos_root_url; int /*<<< orphan*/  url; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  rev; } ;
typedef  TYPE_1__ svn_client__pathrev_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* apr_palloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_path_url_add_component2 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__node_get_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__wc_node_get_base(svn_client__pathrev_t **base_p,
                             const char *wc_abspath,
                             svn_wc_context_t *wc_ctx,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  const char *relpath;

  *base_p = apr_palloc(result_pool, sizeof(**base_p));

  SVN_ERR(svn_wc__node_get_base(NULL,
                                &(*base_p)->rev,
                                &relpath,
                                &(*base_p)->repos_root_url,
                                &(*base_p)->repos_uuid,
                                NULL,
                                wc_ctx, wc_abspath,
                                TRUE /* ignore_enoent */,
                                result_pool, scratch_pool));
  if ((*base_p)->repos_root_url && relpath)
    {
      (*base_p)->url = svn_path_url_add_component2(
                           (*base_p)->repos_root_url, relpath, result_pool);
    }
  else
    {
      *base_p = NULL;
    }
  return SVN_NO_ERROR;
}