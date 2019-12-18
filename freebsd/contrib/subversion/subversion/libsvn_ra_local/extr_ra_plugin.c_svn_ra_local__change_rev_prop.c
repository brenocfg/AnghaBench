#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_6__ {int /*<<< orphan*/  username; int /*<<< orphan*/  repos; } ;
typedef  TYPE_2__ svn_ra_local__session_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_username (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs_change_rev_prop4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const* const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_ra_local__change_rev_prop(svn_ra_session_t *session,
                              svn_revnum_t rev,
                              const char *name,
                              const svn_string_t *const *old_value_p,
                              const svn_string_t *value,
                              apr_pool_t *pool)
{
  svn_ra_local__session_baton_t *sess = session->priv;

  SVN_ERR(get_username(session, pool));
  return svn_repos_fs_change_rev_prop4(sess->repos, rev, sess->username,
                                       name, old_value_p, value, TRUE, TRUE,
                                       NULL, NULL, pool);
}