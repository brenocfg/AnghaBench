#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_8__ {int /*<<< orphan*/  number; } ;
struct TYPE_9__ {TYPE_3__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;
struct TYPE_7__ {TYPE_1__ value; } ;
struct TYPE_10__ {int /*<<< orphan*/  dumpfile; int /*<<< orphan*/  incremental; int /*<<< orphan*/  quiet; TYPE_4__ end_revision; TYPE_2__ start_revision; int /*<<< orphan*/  session; int /*<<< orphan*/  ctx; int /*<<< orphan*/  url; } ;
typedef  TYPE_5__ opt_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_getopt_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * replay_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_client_open_ra_session2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_reparent (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
dump_cmd(apr_getopt_t *os,
         void *baton,
         apr_pool_t *pool)
{
  opt_baton_t *opt_baton = baton;
  svn_ra_session_t *extra_ra_session;
  const char *repos_root;

  SVN_ERR(svn_client_open_ra_session2(&extra_ra_session,
                                      opt_baton->url, NULL,
                                      opt_baton->ctx, pool, pool));
  SVN_ERR(svn_ra_get_repos_root2(extra_ra_session, &repos_root, pool));
  SVN_ERR(svn_ra_reparent(extra_ra_session, repos_root, pool));

  return replay_revisions(opt_baton->session, extra_ra_session,
                          opt_baton->start_revision.value.number,
                          opt_baton->end_revision.value.number,
                          opt_baton->quiet, opt_baton->incremental,
                          opt_baton->dumpfile, pool);
}