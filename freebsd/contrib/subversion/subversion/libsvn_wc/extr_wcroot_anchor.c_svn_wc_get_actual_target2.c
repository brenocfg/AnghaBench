#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ svn_wc_context_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_11__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_WC_NOT_WORKING_COPY ; 
 scalar_t__ SVN_ERR_WC_PATH_NOT_FOUND ; 
 TYPE_2__* SVN_NO_ERROR ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_dirent_get_absolute (char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_split (char const**,char const**,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 scalar_t__ svn_node_dir ; 
 TYPE_2__* svn_wc__db_is_switched (scalar_t__*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc_get_actual_target2(const char **anchor,
                          const char **target,
                          svn_wc_context_t *wc_ctx,
                          const char *path,
                          apr_pool_t *result_pool,
                          apr_pool_t *scratch_pool)
{
  svn_boolean_t is_wc_root, is_switched;
  svn_node_kind_t kind;
  const char *local_abspath;
  svn_error_t *err;

  SVN_ERR(svn_dirent_get_absolute(&local_abspath, path, scratch_pool));

  err = svn_wc__db_is_switched(&is_wc_root, &is_switched, &kind,
                               wc_ctx->db, local_abspath,
                               scratch_pool);

  if (err)
    {
      if (err->apr_err != SVN_ERR_WC_PATH_NOT_FOUND &&
          err->apr_err != SVN_ERR_WC_NOT_WORKING_COPY)
        return svn_error_trace(err);

      svn_error_clear(err);
      is_wc_root = FALSE;
      is_switched = FALSE;
    }

  /* If PATH is not a WC root, or if it is a file, lop off a basename. */
  if (!(is_wc_root || is_switched) || (kind != svn_node_dir))
    {
      svn_dirent_split(anchor, target, path, result_pool);
    }
  else
    {
      *anchor = apr_pstrdup(result_pool, path);
      *target = "";
    }

  return SVN_NO_ERROR;
}