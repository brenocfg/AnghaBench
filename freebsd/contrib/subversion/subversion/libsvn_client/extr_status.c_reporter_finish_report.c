#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_ra_session_t ;
struct TYPE_14__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct TYPE_15__ {int /*<<< orphan*/  wrapped_report_baton; TYPE_1__* wrapped_reporter; int /*<<< orphan*/  pool; int /*<<< orphan*/  set_locks_baton; int /*<<< orphan*/  depth; int /*<<< orphan*/  ctx; int /*<<< orphan*/  ancestor; } ;
typedef  TYPE_3__ report_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;
struct TYPE_13__ {TYPE_2__* (* finish_report ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (TYPE_2__*) ; 
 scalar_t__ SVN_ERR_RA_NOT_IMPLEMENTED ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/ * apr_hash_make (int /*<<< orphan*/ ) ; 
 TYPE_2__* stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_client_open_ra_session2 (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_ra_get_locks2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_ra_get_repos_root2 (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 
 TYPE_2__* svn_wc_status_set_repos_locks (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
reporter_finish_report(void *report_baton, apr_pool_t *pool)
{
  report_baton_t *rb = report_baton;
  svn_ra_session_t *ras;
  apr_hash_t *locks;
  const char *repos_root;
  apr_pool_t *subpool = svn_pool_create(pool);
  svn_error_t *err = SVN_NO_ERROR;

  /* Open an RA session to our common ancestor and grab the locks under it.
   */
  SVN_ERR(svn_client_open_ra_session2(&ras, rb->ancestor, NULL,
                                      rb->ctx, subpool, subpool));

  /* The locks need to live throughout the edit.  Note that if the
     server doesn't support lock discovery, we'll just not do locky
     stuff. */
  err = svn_ra_get_locks2(ras, &locks, "", rb->depth, rb->pool);
  if (err && err->apr_err == SVN_ERR_RA_NOT_IMPLEMENTED)
    {
      svn_error_clear(err);
      err = SVN_NO_ERROR;
      locks = apr_hash_make(rb->pool);
    }
  SVN_ERR(err);

  SVN_ERR(svn_ra_get_repos_root2(ras, &repos_root, rb->pool));

  /* Close the RA session. */
  svn_pool_destroy(subpool);

  SVN_ERR(svn_wc_status_set_repos_locks(rb->set_locks_baton, locks,
                                        repos_root, rb->pool));

  return rb->wrapped_reporter->finish_report(rb->wrapped_report_baton, pool);
}