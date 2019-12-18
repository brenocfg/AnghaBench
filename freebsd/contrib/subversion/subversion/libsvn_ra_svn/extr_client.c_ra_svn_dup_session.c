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
struct TYPE_6__ {int /*<<< orphan*/  config; int /*<<< orphan*/  auth_baton; int /*<<< orphan*/  callbacks_baton; int /*<<< orphan*/  callbacks; } ;
typedef  TYPE_1__ svn_ra_svn__session_baton_t ;
struct TYPE_7__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  ra_svn_open (TYPE_2__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *ra_svn_dup_session(svn_ra_session_t *new_session,
                                       svn_ra_session_t *old_session,
                                       const char *new_session_url,
                                       apr_pool_t *result_pool,
                                       apr_pool_t *scratch_pool)
{
  svn_ra_svn__session_baton_t *old_sess = old_session->priv;

  SVN_ERR(ra_svn_open(new_session, NULL, new_session_url,
                      old_sess->callbacks, old_sess->callbacks_baton,
                      old_sess->auth_baton, old_sess->config,
                      result_pool, scratch_pool));

  return SVN_NO_ERROR;
}