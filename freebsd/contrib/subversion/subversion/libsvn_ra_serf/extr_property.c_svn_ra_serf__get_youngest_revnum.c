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
typedef  int /*<<< orphan*/  svn_ra_serf__session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_RA_SERF__HAVE_HTTPV2_SUPPORT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_trace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_ra_serf__discover_vcc (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_serf__v2_get_youngest_revnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v1_get_youngest_revnum (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_ra_serf__get_youngest_revnum(svn_revnum_t *youngest,
                                 svn_ra_serf__session_t *session,
                                 apr_pool_t *scratch_pool)
{
  const char *vcc_url;

  if (SVN_RA_SERF__HAVE_HTTPV2_SUPPORT(session))
    return svn_error_trace(svn_ra_serf__v2_get_youngest_revnum(
                             youngest, session, scratch_pool));

  SVN_ERR(svn_ra_serf__discover_vcc(&vcc_url, session, scratch_pool));

  return svn_error_trace(v1_get_youngest_revnum(youngest, NULL,
                                                session, vcc_url,
                                                scratch_pool, scratch_pool));
}