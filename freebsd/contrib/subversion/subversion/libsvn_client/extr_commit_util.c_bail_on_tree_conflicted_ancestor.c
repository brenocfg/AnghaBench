#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  (* svn_wc_notify_func2_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_wc_context_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_FOUND_CONFLICT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 char* svn_dirent_dirname (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_dirent_is_ancestor (char const*,char const*) ; 
 scalar_t__ svn_dirent_is_root (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__get_wcroot (char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_conflicted_p3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_create_notify (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc_notify_failed_conflict ; 

__attribute__((used)) static svn_error_t *
bail_on_tree_conflicted_ancestor(svn_wc_context_t *wc_ctx,
                                 const char *local_abspath,
                                 svn_wc_notify_func2_t notify_func,
                                 void *notify_baton,
                                 apr_pool_t *scratch_pool)
{
  const char *wcroot_abspath;

  SVN_ERR(svn_wc__get_wcroot(&wcroot_abspath, wc_ctx, local_abspath,
                             scratch_pool, scratch_pool));

  local_abspath = svn_dirent_dirname(local_abspath, scratch_pool);

  while(svn_dirent_is_ancestor(wcroot_abspath, local_abspath))
    {
      svn_boolean_t tree_conflicted;

      /* Check if the parent has tree conflicts */
      SVN_ERR(svn_wc_conflicted_p3(NULL, NULL, &tree_conflicted,
                                   wc_ctx, local_abspath, scratch_pool));
      if (tree_conflicted)
        {
          if (notify_func != NULL)
            {
              notify_func(notify_baton,
                          svn_wc_create_notify(local_abspath,
                                               svn_wc_notify_failed_conflict,
                                               scratch_pool),
                          scratch_pool);
            }

          return svn_error_createf(
                   SVN_ERR_WC_FOUND_CONFLICT, NULL,
                   _("Aborting commit: '%s' remains in tree-conflict"),
                   svn_dirent_local_style(local_abspath, scratch_pool));
        }

      /* Step outwards */
      if (svn_dirent_is_root(local_abspath, strlen(local_abspath)))
        break;
      else
        local_abspath = svn_dirent_dirname(local_abspath, scratch_pool);
    }

  return SVN_NO_ERROR;
}