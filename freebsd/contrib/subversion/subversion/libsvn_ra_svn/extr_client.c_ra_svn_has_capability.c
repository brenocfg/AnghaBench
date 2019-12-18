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
struct TYPE_4__ {int /*<<< orphan*/  conn; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
struct TYPE_5__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_UNKNOWN_CAPABILITY ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
#define  SVN_RA_CAPABILITY_ATOMIC_REVPROPS 147 
#define  SVN_RA_CAPABILITY_COMMIT_REVPROPS 146 
#define  SVN_RA_CAPABILITY_DEPTH 145 
#define  SVN_RA_CAPABILITY_EPHEMERAL_TXNPROPS 144 
#define  SVN_RA_CAPABILITY_GET_FILE_REVS_REVERSE 143 
#define  SVN_RA_CAPABILITY_INHERITED_PROPS 142 
#define  SVN_RA_CAPABILITY_LIST 141 
#define  SVN_RA_CAPABILITY_LOG_REVPROPS 140 
#define  SVN_RA_CAPABILITY_MERGEINFO 139 
#define  SVN_RA_CAPABILITY_PARTIAL_REPLAY 138 
#define  SVN_RA_SVN_CAP_ATOMIC_REVPROPS 137 
#define  SVN_RA_SVN_CAP_COMMIT_REVPROPS 136 
#define  SVN_RA_SVN_CAP_DEPTH 135 
#define  SVN_RA_SVN_CAP_EPHEMERAL_TXNPROPS 134 
#define  SVN_RA_SVN_CAP_GET_FILE_REVS_REVERSE 133 
#define  SVN_RA_SVN_CAP_INHERITED_PROPS 132 
#define  SVN_RA_SVN_CAP_LIST 131 
#define  SVN_RA_SVN_CAP_LOG_REVPROPS 130 
#define  SVN_RA_SVN_CAP_MERGEINFO 129 
#define  SVN_RA_SVN_CAP_PARTIAL_REPLAY 128 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_ra_svn_has_capability (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static svn_error_t *
ra_svn_has_capability(svn_ra_session_t *session,
                      svn_boolean_t *has,
                      const char *capability,
                      apr_pool_t *pool)
{
  svn_ra_svn__session_baton_t *sess = session->priv;
  static const char* capabilities[][2] =
  {
      /* { ra capability string, svn:// wire capability string} */
      {SVN_RA_CAPABILITY_DEPTH, SVN_RA_SVN_CAP_DEPTH},
      {SVN_RA_CAPABILITY_MERGEINFO, SVN_RA_SVN_CAP_MERGEINFO},
      {SVN_RA_CAPABILITY_LOG_REVPROPS, SVN_RA_SVN_CAP_LOG_REVPROPS},
      {SVN_RA_CAPABILITY_PARTIAL_REPLAY, SVN_RA_SVN_CAP_PARTIAL_REPLAY},
      {SVN_RA_CAPABILITY_COMMIT_REVPROPS, SVN_RA_SVN_CAP_COMMIT_REVPROPS},
      {SVN_RA_CAPABILITY_ATOMIC_REVPROPS, SVN_RA_SVN_CAP_ATOMIC_REVPROPS},
      {SVN_RA_CAPABILITY_INHERITED_PROPS, SVN_RA_SVN_CAP_INHERITED_PROPS},
      {SVN_RA_CAPABILITY_EPHEMERAL_TXNPROPS,
                                          SVN_RA_SVN_CAP_EPHEMERAL_TXNPROPS},
      {SVN_RA_CAPABILITY_GET_FILE_REVS_REVERSE,
                                       SVN_RA_SVN_CAP_GET_FILE_REVS_REVERSE},
      {SVN_RA_CAPABILITY_LIST, SVN_RA_SVN_CAP_LIST},

      {NULL, NULL} /* End of list marker */
  };
  int i;

  *has = FALSE;

  for (i = 0; capabilities[i][0]; i++)
    {
      if (strcmp(capability, capabilities[i][0]) == 0)
        {
          *has = svn_ra_svn_has_capability(sess->conn, capabilities[i][1]);
          return SVN_NO_ERROR;
        }
    }

  return svn_error_createf(SVN_ERR_UNKNOWN_CAPABILITY, NULL,
                           _("Don't know anything about capability '%s'"),
                           capability);
}