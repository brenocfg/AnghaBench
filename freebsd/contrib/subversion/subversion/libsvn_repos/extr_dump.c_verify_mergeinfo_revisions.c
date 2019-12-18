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
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_notify_func_t ;
typedef  int /*<<< orphan*/  svn_mergeinfo_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ apr_hash_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  notify_warning (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_mergeinfo__filter_mergeinfo_by_ranges (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_mergeinfo_parse (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_notify_warning_found_old_mergeinfo ; 

__attribute__((used)) static svn_error_t *
verify_mergeinfo_revisions(svn_boolean_t *found_old_mergeinfo,
                           const char *mergeinfo_str,
                           svn_revnum_t oldest_dumped_rev,
                           svn_repos_notify_func_t notify_func,
                           void *notify_baton,
                           apr_pool_t *pool)
{
  svn_mergeinfo_t mergeinfo, old_mergeinfo;

  SVN_ERR(svn_mergeinfo_parse(&mergeinfo, mergeinfo_str, pool));
  SVN_ERR(svn_mergeinfo__filter_mergeinfo_by_ranges(
            &old_mergeinfo, mergeinfo,
            oldest_dumped_rev - 1, 0,
            TRUE, pool, pool));

  if (apr_hash_count(old_mergeinfo))
    {
      notify_warning(pool, notify_func, notify_baton,
                     svn_repos_notify_warning_found_old_mergeinfo,
                     _("Mergeinfo referencing revision(s) prior "
                       "to the oldest dumped revision (r%ld). "
                       "Loading this dump may result in invalid "
                       "mergeinfo."),
                     oldest_dumped_rev);

      if (found_old_mergeinfo)
        *found_old_mergeinfo = TRUE;
    }

  return SVN_NO_ERROR;
}