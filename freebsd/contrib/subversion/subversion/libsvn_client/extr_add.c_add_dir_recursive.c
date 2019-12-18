#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_magic__cookie_t ;
struct TYPE_21__ {scalar_t__ kind; scalar_t__ special; } ;
typedef  TYPE_1__ svn_io_dirent2_t ;
struct TYPE_22__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  scalar_t__ svn_depth_t ;
struct TYPE_23__ {int /*<<< orphan*/  cancel_baton; TYPE_2__* (* cancel_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  config; int /*<<< orphan*/  wc_ctx; int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  notify_func2; } ;
typedef  TYPE_3__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_ENTRY_EXISTS ; 
 TYPE_2__* SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 TYPE_2__* add_file (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 TYPE_1__* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 TYPE_2__* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__* stub2 (int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_client__get_all_auto_props (int /*<<< orphan*/ **,char const*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_io_get_dirents3 (int /*<<< orphan*/ **,char const*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_add_from_disk3 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_wc_get_ignores2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_is_adm_dir (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_match_ignore_list (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
add_dir_recursive(const char *dir_abspath,
                  svn_depth_t depth,
                  svn_boolean_t force,
                  svn_boolean_t no_autoprops,
                  svn_magic__cookie_t *magic_cookie,
                  apr_hash_t *config_autoprops,
                  svn_boolean_t refresh_ignores,
                  apr_array_header_t *ignores,
                  svn_client_ctx_t *ctx,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  svn_error_t *err;
  apr_pool_t *iterpool;
  apr_hash_t *dirents;
  apr_hash_index_t *hi;
  svn_boolean_t entry_exists = FALSE;

  /* Check cancellation; note that this catches recursive calls too. */
  if (ctx->cancel_func)
    SVN_ERR(ctx->cancel_func(ctx->cancel_baton));

  iterpool = svn_pool_create(scratch_pool);

  /* Add this directory to revision control. */
  err = svn_wc_add_from_disk3(ctx->wc_ctx, dir_abspath, NULL /*props*/,
                              FALSE /* skip checks */,
                              ctx->notify_func2, ctx->notify_baton2,
                              iterpool);
  if (err)
    {
      if (err->apr_err == SVN_ERR_ENTRY_EXISTS && force)
        {
          svn_error_clear(err);
          entry_exists = TRUE;
        }
      else if (err)
        {
          return svn_error_trace(err);
        }
    }

  /* Fetch ignores after adding to handle ignores on the directory itself
     and ancestors via the single db optimization in libsvn_wc */
  if (refresh_ignores)
    SVN_ERR(svn_wc_get_ignores2(&ignores, ctx->wc_ctx, dir_abspath,
                                ctx->config, result_pool, iterpool));

  /* If DIR_ABSPATH is the root of an unversioned subtree then get the
     following "autoprops":

       1) Explicit and inherited svn:auto-props properties on
          DIR_ABSPATH
       2) auto-props from the CTX->CONFIG hash

     Since this set of autoprops applies to all unversioned children of
     DIR_ABSPATH, we will pass these along to any recursive calls to
     add_dir_recursive() and calls to add_file() below.  Thus sparing
     these callees from looking up the same information. */
  if (!entry_exists && config_autoprops == NULL)
    {
      SVN_ERR(svn_client__get_all_auto_props(&config_autoprops, dir_abspath,
                                             ctx, scratch_pool, iterpool));
    }

  SVN_ERR(svn_io_get_dirents3(&dirents, dir_abspath, TRUE, scratch_pool,
                              iterpool));

  /* Read the directory entries one by one and add those things to
     version control. */
  for (hi = apr_hash_first(scratch_pool, dirents); hi; hi = apr_hash_next(hi))
    {
      const char *name = apr_hash_this_key(hi);
      svn_io_dirent2_t *dirent = apr_hash_this_val(hi);
      const char *abspath;

      svn_pool_clear(iterpool);

      /* Check cancellation so you can cancel during an
       * add of a directory with lots of files. */
      if (ctx->cancel_func)
        SVN_ERR(ctx->cancel_func(ctx->cancel_baton));

      /* Skip over SVN admin directories. */
      if (svn_wc_is_adm_dir(name, iterpool))
        continue;

      if (ignores
          && svn_wc_match_ignore_list(name, ignores, iterpool))
        continue;

      /* Construct the full path of the entry. */
      abspath = svn_dirent_join(dir_abspath, name, iterpool);

      /* Recurse on directories; add files; ignore the rest. */
      if (dirent->kind == svn_node_dir && depth >= svn_depth_immediates)
        {
          svn_depth_t depth_below_here = depth;
          if (depth == svn_depth_immediates)
            depth_below_here = svn_depth_empty;

          /* When DIR_ABSPATH is the root of an unversioned subtree then
             it and all of its children have the same set of ignores.  So
             save any recursive calls the extra work of finding the same
             set of ignores. */
          if (refresh_ignores && !entry_exists)
            refresh_ignores = FALSE;

          SVN_ERR(add_dir_recursive(abspath, depth_below_here,
                                    force, no_autoprops,
                                    magic_cookie, config_autoprops,
                                    refresh_ignores, ignores, ctx,
                                    result_pool, iterpool));
        }
      else if ((dirent->kind == svn_node_file || dirent->special)
               && depth >= svn_depth_files)
        {
          err = add_file(abspath, magic_cookie, config_autoprops,
                         no_autoprops, ctx, iterpool);
          if (err && err->apr_err == SVN_ERR_ENTRY_EXISTS && force)
            svn_error_clear(err);
          else
            SVN_ERR(err);
        }
    }

  /* Destroy the per-iteration pool. */
  svn_pool_destroy(iterpool);

  return SVN_NO_ERROR;
}