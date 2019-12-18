#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
struct ra_ev2_baton {int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  relpath_map; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 char* svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_wc__node_get_origin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_get_pristine_props (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__ra_provide_props(apr_hash_t **props,
                             svn_revnum_t *revision,
                             void *baton,
                             const char *repos_relpath,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  struct ra_ev2_baton *reb = baton;
  const char *local_abspath;
  svn_error_t *err;

  local_abspath = svn_hash_gets(reb->relpath_map, repos_relpath);
  if (!local_abspath)
    {
      *props = NULL;
      return SVN_NO_ERROR;
    }

  err = svn_wc_get_pristine_props(props, reb->wc_ctx, local_abspath,
                                  result_pool, scratch_pool);
  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND)
        return svn_error_trace(err);

      svn_error_clear(err);
      *props = NULL;
      return SVN_NO_ERROR;
    }

  if (*props != NULL)
    {
      /* The pristine props refer to the BASE, or to the pristine props of
         a copy/move to this location. Fetch the correct revision.  */
      SVN_ERR(svn_wc__node_get_origin(NULL, revision, NULL, NULL, NULL, NULL,
                                      NULL,
                                      reb->wc_ctx, local_abspath, FALSE,
                                      scratch_pool, scratch_pool));
    }

  return SVN_NO_ERROR;
}