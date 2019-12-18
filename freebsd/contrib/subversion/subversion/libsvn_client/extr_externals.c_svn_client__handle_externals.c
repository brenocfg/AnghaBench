#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_14__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_depth_t ;
struct TYPE_15__ {int /*<<< orphan*/  wc_ctx; } ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 scalar_t__ APR_STATUS_IS_ENOENT (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_ENOTDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ APR_STATUS_IS_ENOTEMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (char const*) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* apr_hash_get (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apr_hash_this_key_len (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_external_item_removal (TYPE_2__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_externals_change (TYPE_2__*,char const*,int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  svn_depth_from_word (char const*) ; 
 int /*<<< orphan*/  svn_depth_infinity ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 TYPE_1__* svn_io_dir_remove_nonrecursive (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_none ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__externals_defined_below (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_read_kind2 (scalar_t__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrap_external_error (TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_client__handle_externals(apr_hash_t *externals_new,
                             apr_hash_t *ambient_depths,
                             const char *repos_root_url,
                             const char *target_abspath,
                             svn_depth_t requested_depth,
                             svn_boolean_t *timestamp_sleep,
                             svn_ra_session_t *ra_session,
                             svn_client_ctx_t *ctx,
                             apr_pool_t *scratch_pool)
{
  apr_hash_t *old_external_defs;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool;

  SVN_ERR_ASSERT(repos_root_url);

  iterpool = svn_pool_create(scratch_pool);

  SVN_ERR(svn_wc__externals_defined_below(&old_external_defs,
                                          ctx->wc_ctx, target_abspath,
                                          scratch_pool, iterpool));

  for (hi = apr_hash_first(scratch_pool, externals_new);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *local_abspath = apr_hash_this_key(hi);
      const char *desc_text = apr_hash_this_val(hi);
      svn_depth_t ambient_depth = svn_depth_infinity;

      svn_pool_clear(iterpool);

      if (ambient_depths)
        {
          const char *ambient_depth_w;

          ambient_depth_w = apr_hash_get(ambient_depths, local_abspath,
                                         apr_hash_this_key_len(hi));

          if (ambient_depth_w == NULL)
            {
              return svn_error_createf(
                        SVN_ERR_WC_CORRUPT, NULL,
                        _("Traversal of '%s' found no ambient depth"),
                        svn_dirent_local_style(local_abspath, scratch_pool));
            }
          else
            {
              ambient_depth = svn_depth_from_word(ambient_depth_w);
            }
        }

      SVN_ERR(handle_externals_change(ctx, repos_root_url, timestamp_sleep,
                                      local_abspath,
                                      desc_text, old_external_defs,
                                      ambient_depth, requested_depth,
                                      ra_session, iterpool));
    }

  /* Remove the remaining externals */
  for (hi = apr_hash_first(scratch_pool, old_external_defs);
       hi;
       hi = apr_hash_next(hi))
    {
      const char *item_abspath = apr_hash_this_key(hi);
      const char *defining_abspath = apr_hash_this_val(hi);
      const char *parent_abspath;

      svn_pool_clear(iterpool);

      SVN_ERR(wrap_external_error(
                          ctx, item_abspath,
                          handle_external_item_removal(ctx, defining_abspath,
                                                       item_abspath, iterpool),
                          iterpool));

      /* Are there any unversioned directories between the removed
       * external and the DEFINING_ABSPATH which we can remove? */
      parent_abspath = item_abspath;
      do {
        svn_node_kind_t kind;

        parent_abspath = svn_dirent_dirname(parent_abspath, iterpool);
        SVN_ERR(svn_wc_read_kind2(&kind, ctx->wc_ctx, parent_abspath,
                                  FALSE /* show_deleted*/,
                                  FALSE /* show_hidden */,
                                  iterpool));
        if (kind == svn_node_none)
          {
            svn_error_t *err;

            err = svn_io_dir_remove_nonrecursive(parent_abspath, iterpool);
            if (err)
              {
                if (APR_STATUS_IS_ENOTEMPTY(err->apr_err))
                  {
                    svn_error_clear(err);
                    break; /* No parents to delete */
                  }
                else if (APR_STATUS_IS_ENOENT(err->apr_err)
                         || APR_STATUS_IS_ENOTDIR(err->apr_err))
                  {
                    svn_error_clear(err);
                    /* Fall through; parent dir might be unversioned */
                  }
                else
                  return svn_error_trace(err);
              }
          }
      } while (strcmp(parent_abspath, defining_abspath) != 0);
    }


  svn_pool_destroy(iterpool);
  return SVN_NO_ERROR;
}