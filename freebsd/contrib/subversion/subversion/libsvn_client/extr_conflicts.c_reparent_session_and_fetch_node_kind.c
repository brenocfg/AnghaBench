#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_node_kind_t ;
struct TYPE_8__ {scalar_t__ apr_err; } ;
typedef  TYPE_1__ svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_ERR_RA_ILLEGAL_URL ; 
 TYPE_1__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_1__*) ; 
 TYPE_1__* svn_error_trace (TYPE_1__*) ; 
 int /*<<< orphan*/  svn_node_unknown ; 
 int /*<<< orphan*/  svn_ra_check_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
reparent_session_and_fetch_node_kind(svn_node_kind_t *node_kind,
                                     svn_ra_session_t *ra_session,
                                     const char *url,
                                     svn_revnum_t peg_rev,
                                     apr_pool_t *scratch_pool)
{
  svn_error_t *err;

  err = svn_ra_reparent(ra_session, url, scratch_pool);
  if (err)
    {
      if (err->apr_err == SVN_ERR_RA_ILLEGAL_URL)
        {
          svn_error_clear(err);
          *node_kind = svn_node_unknown;
          return SVN_NO_ERROR;
        }
    
      return svn_error_trace(err);
    }

  SVN_ERR(svn_ra_check_path(ra_session, "", peg_rev, node_kind, scratch_pool));

  return SVN_NO_ERROR;
}