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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct check_url_kind_baton {int /*<<< orphan*/  session; int /*<<< orphan*/  should_reparent; int /*<<< orphan*/  repos_root_url; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_node_none ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
check_url_kind(void *baton,
               svn_node_kind_t *kind,
               const char *url,
               svn_revnum_t revision,
               apr_pool_t *scratch_pool)
{
  struct check_url_kind_baton *cukb = baton;

  /* If we don't have a session or can't use the session, get one */
  if (!svn_uri__is_ancestor(cukb->repos_root_url, url))
    *kind = svn_node_none;
  else
    {
      cukb->should_reparent = TRUE;

      SVN_ERR(svn_ra_reparent(cukb->session, url, scratch_pool));

      SVN_ERR(svn_ra_check_path(cukb->session, "", revision,
                                kind, scratch_pool));
    }

  return SVN_NO_ERROR;
}