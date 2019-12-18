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
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
#define  SVN_REPOS_CAPABILITY_MERGEINFO 128 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ *,char const* const,char const* const) ; 
 int /*<<< orphan*/  svn_repos_has_capability (int /*<<< orphan*/ *,scalar_t__*,char const* const,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_repos_capabilities(apr_hash_t **capabilities,
                       svn_repos_t *repos,
                       apr_pool_t *result_pool,
                       apr_pool_t *scratch_pool)
{
  static const char *const queries[] = {
    SVN_REPOS_CAPABILITY_MERGEINFO,
    NULL
  };
  const char *const *i;

  *capabilities = apr_hash_make(result_pool);

  for (i = queries; *i; i++)
    {
      svn_boolean_t has;
      SVN_ERR(svn_repos_has_capability(repos, &has, *i, scratch_pool));
      if (has)
        svn_hash_sets(*capabilities, *i, *i);
    }

  return SVN_NO_ERROR;
}