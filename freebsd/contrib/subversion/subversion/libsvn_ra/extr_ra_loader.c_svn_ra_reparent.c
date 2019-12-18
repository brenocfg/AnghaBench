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
struct TYPE_7__ {TYPE_1__* vtable; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {int /*<<< orphan*/ * (* reparent ) (TYPE_2__*,char const*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_RA_ILLEGAL_URL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (TYPE_2__*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_uri__is_ancestor (char const*,char const*) ; 

svn_error_t *svn_ra_reparent(svn_ra_session_t *session,
                             const char *url,
                             apr_pool_t *pool)
{
  const char *repos_root;

  /* Make sure the new URL is in the same repository, so that the
     implementations don't have to do it. */
  SVN_ERR(svn_ra_get_repos_root2(session, &repos_root, pool));
  if (! svn_uri__is_ancestor(repos_root, url))
    return svn_error_createf(SVN_ERR_RA_ILLEGAL_URL, NULL,
                             _("'%s' isn't in the same repository as '%s'"),
                             url, repos_root);

  return session->vtable->reparent(session, url, pool);
}