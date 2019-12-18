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
typedef  int /*<<< orphan*/  (* svn_wc_upgrade_get_repos_info_t ) (int /*<<< orphan*/ **,int /*<<< orphan*/ **,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;
struct TYPE_3__ {int /*<<< orphan*/ * url; int /*<<< orphan*/ * uuid; int /*<<< orphan*/ * repos; } ;
typedef  TYPE_1__ svn_wc_entry_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
typedef  int /*<<< orphan*/  apr_hash_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_WC_UNSUPPORTED_FORMAT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * apr_hash_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * apr_hash_this_val (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ **,int /*<<< orphan*/ **,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 scalar_t__ svn_uri__is_ancestor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
ensure_repos_info(svn_wc_entry_t *entry,
                  const char *local_abspath,
                  svn_wc_upgrade_get_repos_info_t repos_info_func,
                  void *repos_info_baton,
                  apr_hash_t *repos_cache,
                  apr_pool_t *result_pool,
                  apr_pool_t *scratch_pool)
{
  /* Easy exit.  */
  if (entry->repos != NULL && entry->uuid != NULL)
    return SVN_NO_ERROR;

  if ((entry->repos == NULL || entry->uuid == NULL)
      && entry->url)
    {
      apr_hash_index_t *hi;

      for (hi = apr_hash_first(scratch_pool, repos_cache);
           hi; hi = apr_hash_next(hi))
        {
          if (svn_uri__is_ancestor(apr_hash_this_key(hi), entry->url))
            {
              if (!entry->repos)
                entry->repos = apr_hash_this_key(hi);

              if (!entry->uuid)
                entry->uuid = apr_hash_this_val(hi);

              return SVN_NO_ERROR;
            }
        }
    }

  if (entry->repos == NULL && repos_info_func == NULL)
    return svn_error_createf(
        SVN_ERR_WC_UNSUPPORTED_FORMAT, NULL,
        _("Working copy '%s' can't be upgraded because the repository root is "
          "not available and can't be retrieved"),
        svn_dirent_local_style(local_abspath, scratch_pool));

  if (entry->uuid == NULL && repos_info_func == NULL)
    return svn_error_createf(
        SVN_ERR_WC_UNSUPPORTED_FORMAT, NULL,
        _("Working copy '%s' can't be upgraded because the repository uuid is "
          "not available and can't be retrieved"),
        svn_dirent_local_style(local_abspath, scratch_pool));

   if (entry->url == NULL)
     return svn_error_createf(
        SVN_ERR_WC_UNSUPPORTED_FORMAT, NULL,
        _("Working copy '%s' can't be upgraded because it doesn't have a url"),
        svn_dirent_local_style(local_abspath, scratch_pool));

   return svn_error_trace((*repos_info_func)(&entry->repos, &entry->uuid,
                                             repos_info_baton,
                                             entry->url,
                                             result_pool, scratch_pool));
}