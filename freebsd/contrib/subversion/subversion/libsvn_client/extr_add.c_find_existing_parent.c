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
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  scalar_t__ svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  cancel_baton; int /*<<< orphan*/ * (* cancel_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * wc_ctx; } ;
typedef  TYPE_1__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SVN_ERR_CLIENT_NO_VERSIONED_PARENT ; 
 int /*<<< orphan*/  SVN_ERR_RESERVED_FILENAME_SPECIFIED ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 char* apr_pstrdup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_basename (char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_wc_is_adm_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_wc_read_kind2 (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
find_existing_parent(const char **existing_parent_abspath,
                     svn_client_ctx_t *ctx,
                     const char *local_abspath,
                     apr_pool_t *result_pool,
                     apr_pool_t *scratch_pool)
{
  svn_node_kind_t kind;
  const char *parent_abspath;
  svn_wc_context_t *wc_ctx = ctx->wc_ctx;

  SVN_ERR(svn_wc_read_kind2(&kind, wc_ctx, local_abspath,
                            FALSE, FALSE, scratch_pool));

  if (kind == svn_node_dir)
    {
      *existing_parent_abspath = apr_pstrdup(result_pool, local_abspath);
      return SVN_NO_ERROR;
    }

  if (svn_dirent_is_root(local_abspath, strlen(local_abspath)))
    return svn_error_create(SVN_ERR_CLIENT_NO_VERSIONED_PARENT, NULL, NULL);

  if (svn_wc_is_adm_dir(svn_dirent_basename(local_abspath, scratch_pool),
                        scratch_pool))
    return svn_error_createf(SVN_ERR_RESERVED_FILENAME_SPECIFIED, NULL,
                             _("'%s' ends in a reserved name"),
                             svn_dirent_local_style(local_abspath,
                                                    scratch_pool));

  parent_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

  if (ctx->cancel_func)
    SVN_ERR(ctx->cancel_func(ctx->cancel_baton));

  SVN_ERR(find_existing_parent(existing_parent_abspath, ctx, parent_abspath,
                               result_pool, scratch_pool));

  return SVN_NO_ERROR;
}