#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ svn_ra_session_t ;
struct TYPE_5__ {int /*<<< orphan*/  repos; } ;
typedef  TYPE_2__ svn_ra_local__session_baton_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_UNKNOWN_CAPABILITY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_ATOMIC_REVPROPS ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_COMMIT_REVPROPS ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_DEPTH ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_EPHEMERAL_TXNPROPS ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_GET_FILE_REVS_REVERSE ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_INHERITED_PROPS ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_LIST ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_LOG_REVPROPS ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_MERGEINFO ; 
 int /*<<< orphan*/  SVN_RA_CAPABILITY_PARTIAL_REPLAY ; 
 int /*<<< orphan*/  SVN_REPOS_CAPABILITY_MERGEINFO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_repos_has_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
svn_ra_local__has_capability(svn_ra_session_t *session,
                             svn_boolean_t *has,
                             const char *capability,
                             apr_pool_t *pool)
{
  svn_ra_local__session_baton_t *sess = session->priv;

  if (strcmp(capability, SVN_RA_CAPABILITY_DEPTH) == 0
      || strcmp(capability, SVN_RA_CAPABILITY_LOG_REVPROPS) == 0
      || strcmp(capability, SVN_RA_CAPABILITY_PARTIAL_REPLAY) == 0
      || strcmp(capability, SVN_RA_CAPABILITY_COMMIT_REVPROPS) == 0
      || strcmp(capability, SVN_RA_CAPABILITY_ATOMIC_REVPROPS) == 0
      || strcmp(capability, SVN_RA_CAPABILITY_INHERITED_PROPS) == 0
      || strcmp(capability, SVN_RA_CAPABILITY_EPHEMERAL_TXNPROPS) == 0
      || strcmp(capability, SVN_RA_CAPABILITY_GET_FILE_REVS_REVERSE) == 0
      || strcmp(capability, SVN_RA_CAPABILITY_LIST) == 0
      )
    {
      *has = TRUE;
    }
  else if (strcmp(capability, SVN_RA_CAPABILITY_MERGEINFO) == 0)
    {
      /* With mergeinfo, the code's capabilities may not reflect the
         repository's, so inquire further. */
      SVN_ERR(svn_repos_has_capability(sess->repos, has,
                                       SVN_REPOS_CAPABILITY_MERGEINFO,
                                       pool));
    }
  else  /* Don't know any other capabilities, so error. */
    {
      return svn_error_createf
        (SVN_ERR_UNKNOWN_CAPABILITY, NULL,
         _("Don't know anything about capability '%s'"), capability);
    }

  return SVN_NO_ERROR;
}