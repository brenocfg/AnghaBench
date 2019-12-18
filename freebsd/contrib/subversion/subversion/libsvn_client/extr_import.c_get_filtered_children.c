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
struct TYPE_6__ {int /*<<< orphan*/  lock_state; int /*<<< orphan*/  prop_state; int /*<<< orphan*/  content_state; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_wc_notify_t ;
typedef  int /*<<< orphan*/  svn_io_dirent2_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  (* svn_client_import_filter_func_t ) (void*,scalar_t__*,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;
struct TYPE_7__ {int /*<<< orphan*/  notify_baton2; int /*<<< orphan*/  (* notify_func2 ) (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ svn_client_ctx_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;
typedef  int /*<<< orphan*/  apr_array_header_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 char* apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_hash_gets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_get_dirents3 (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_node_dir ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_wc_create_notify (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_is_adm_dir (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_wc_match_ignore_list (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_lock_state_inapplicable ; 
 int /*<<< orphan*/  svn_wc_notify_skip ; 
 int /*<<< orphan*/  svn_wc_notify_state_inapplicable ; 

__attribute__((used)) static svn_error_t *
get_filtered_children(apr_hash_t **children,
                      const char *dir_abspath,
                      apr_hash_t *excludes,
                      apr_array_header_t *ignores,
                      apr_array_header_t *global_ignores,
                      svn_client_import_filter_func_t filter_callback,
                      void *filter_baton,
                      svn_client_ctx_t *ctx,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  apr_hash_t *dirents;
  apr_hash_index_t *hi;
  apr_pool_t *iterpool = svn_pool_create(scratch_pool);

  SVN_ERR(svn_io_get_dirents3(&dirents, dir_abspath, TRUE, result_pool,
                              scratch_pool));

  for (hi = apr_hash_first(scratch_pool, dirents); hi; hi = apr_hash_next(hi))
    {
      const char *base_name = apr_hash_this_key(hi);
      const svn_io_dirent2_t *dirent = apr_hash_this_val(hi);
      const char *local_abspath;

      svn_pool_clear(iterpool);

      local_abspath = svn_dirent_join(dir_abspath, base_name, iterpool);

      if (svn_wc_is_adm_dir(base_name, iterpool))
        {
          /* If someone's trying to import a directory named the same
             as our administrative directories, that's probably not
             what they wanted to do.  If they are importing a file
             with that name, something is bound to blow up when they
             checkout what they've imported.  So, just skip items with
             that name.  */
          if (ctx->notify_func2)
            {
              svn_wc_notify_t *notify
                = svn_wc_create_notify(svn_dirent_join(local_abspath, base_name,
                                                       iterpool),
                                       svn_wc_notify_skip, iterpool);
              notify->kind = svn_node_dir;
              notify->content_state = notify->prop_state
                = svn_wc_notify_state_inapplicable;
              notify->lock_state = svn_wc_notify_lock_state_inapplicable;
              ctx->notify_func2(ctx->notify_baton2, notify, iterpool);
            }

          svn_hash_sets(dirents, base_name, NULL);
          continue;
        }
            /* If this is an excluded path, exclude it. */
      if (svn_hash_gets(excludes, local_abspath))
        {
          svn_hash_sets(dirents, base_name, NULL);
          continue;
        }

      if (ignores && svn_wc_match_ignore_list(base_name, ignores, iterpool))
        {
          svn_hash_sets(dirents, base_name, NULL);
          continue;
        }

      if (global_ignores &&
          svn_wc_match_ignore_list(base_name, global_ignores, iterpool))
        {
          svn_hash_sets(dirents, base_name, NULL);
          continue;
        }

      if (filter_callback)
        {
          svn_boolean_t filter = FALSE;

          SVN_ERR(filter_callback(filter_baton, &filter, local_abspath,
                                  dirent, iterpool));

          if (filter)
            {
              svn_hash_sets(dirents, base_name, NULL);
              continue;
            }
        }
    }
  svn_pool_destroy(iterpool);

  *children = dirents;
  return SVN_NO_ERROR;
}