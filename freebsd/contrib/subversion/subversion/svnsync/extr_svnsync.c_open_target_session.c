#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_4__ {int /*<<< orphan*/  to_url; int /*<<< orphan*/  config; int /*<<< orphan*/  sync_callbacks; } ;
typedef  TYPE_1__ subcommand_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  check_if_session_is_at_repos_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_open4 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_target_session(svn_ra_session_t **target_session_p,
                    subcommand_baton_t *baton,
                    apr_pool_t *pool)
{
  svn_ra_session_t *target_session;
  SVN_ERR(svn_ra_open4(&target_session, NULL, baton->to_url, NULL,
                       &(baton->sync_callbacks), baton, baton->config, pool));
  SVN_ERR(check_if_session_is_at_repos_root(target_session, baton->to_url, pool));

  *target_session_p = target_session;
  return SVN_NO_ERROR;
}