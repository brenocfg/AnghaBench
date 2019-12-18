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
struct TYPE_3__ {int /*<<< orphan*/  repos_url; int /*<<< orphan*/  repos_uuid; int /*<<< orphan*/  path_in_repos; int /*<<< orphan*/  peg_rev; int /*<<< orphan*/  node_kind; } ;
typedef  TYPE_1__ svn_wc_conflict_version_t ;
typedef  int /*<<< orphan*/  svn_skel_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__CONFLICT_SRC_SUBVERSION ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_node_kind_to_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_skel__make_empty_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_skel__prepend_str (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
conflict__prepend_location(svn_skel_t *skel,
                           const svn_wc_conflict_version_t *location,
                           svn_boolean_t allow_NULL,
                           apr_pool_t *result_pool,
                           apr_pool_t *scratch_pool)
{
  svn_skel_t *loc;
  SVN_ERR_ASSERT(location || allow_NULL);

  if (!location)
    {
      svn_skel__prepend(svn_skel__make_empty_list(result_pool), skel);
      return SVN_NO_ERROR;
    }

  /* ("subversion" repos_root_url repos_uuid repos_relpath rev kind) */
  loc = svn_skel__make_empty_list(result_pool);

  svn_skel__prepend_str(svn_node_kind_to_word(location->node_kind),
                        loc, result_pool);

  svn_skel__prepend_int(location->peg_rev, loc, result_pool);

  svn_skel__prepend_str(apr_pstrdup(result_pool, location->path_in_repos), loc,
                        result_pool);

  if (!location->repos_uuid) /* Can theoretically be NULL */
    svn_skel__prepend(svn_skel__make_empty_list(result_pool), loc);
  else
    svn_skel__prepend_str(location->repos_uuid, loc, result_pool);

  svn_skel__prepend_str(apr_pstrdup(result_pool, location->repos_url), loc,
                        result_pool);

  svn_skel__prepend_str(SVN_WC__CONFLICT_SRC_SUBVERSION, loc, result_pool);

  svn_skel__prepend(loc, skel);
  return SVN_NO_ERROR;
}