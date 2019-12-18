#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_1__*) ; 
 scalar_t__ SVN_ERR_ILLEGAL_TARGET ; 
 TYPE_1__* SVN_NO_ERROR ; 
 TYPE_1__* shelf_apply_patch (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* shelf_delete_patch (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_client_get_wc_root (char const**,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_error_quick_wrapf (TYPE_1__*,char*,char const*) ; 

svn_error_t *
svn_client_unshelve(const char *name,
                    const char *local_abspath,
                    svn_boolean_t keep,
                    svn_boolean_t dry_run,
                    svn_client_ctx_t *ctx,
                    apr_pool_t *pool)
{
  const char *wc_root_abspath;
  svn_error_t *err;

  SVN_ERR(svn_client_get_wc_root(&wc_root_abspath,
                                 local_abspath, ctx, pool, pool));

  /* Apply the patch. */
  err = shelf_apply_patch(name, wc_root_abspath,
                          FALSE /*reverse*/, dry_run,
                          ctx, pool);
  if (err && err->apr_err == SVN_ERR_ILLEGAL_TARGET)
    {
      return svn_error_quick_wrapf(err,
                                   "Shelved change '%s' not found",
                                   name);
    }
  else
    SVN_ERR(err);

  /* Remove the patch. */
  if (! keep && ! dry_run)
    {
      SVN_ERR(shelf_delete_patch(name, wc_root_abspath,
                                 ctx, pool));
    }

  return SVN_NO_ERROR;
}