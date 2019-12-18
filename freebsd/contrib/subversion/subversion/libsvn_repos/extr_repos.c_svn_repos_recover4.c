#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  db_path; } ;
typedef  TYPE_1__ svn_repos_t ;
struct TYPE_8__ {int /*<<< orphan*/  action; } ;
typedef  TYPE_2__ svn_repos_notify_t ;
typedef  int /*<<< orphan*/  (* svn_repos_notify_func_t ) (void*,TYPE_2__*,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_cancel_func_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_repos (TYPE_1__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_recover (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_repos_notify_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos_notify_mutex_acquired ; 
 int /*<<< orphan*/  svn_repos_notify_recover_start ; 

svn_error_t *
svn_repos_recover4(const char *path,
                   svn_boolean_t nonblocking,
                   svn_repos_notify_func_t notify_func,
                   void *notify_baton,
                   svn_cancel_func_t cancel_func,
                   void * cancel_baton,
                   apr_pool_t *pool)
{
  svn_repos_t *repos;
  apr_pool_t *subpool = svn_pool_create(pool);

  /* Fetch a repository object; for the Berkeley DB backend, it is
     initialized with an EXCLUSIVE lock on the database.  This will at
     least prevent others from trying to read or write to it while we
     run recovery. (Other backends should do their own locking; see
     lock_repos.) */
  SVN_ERR(get_repos(&repos, path, TRUE, nonblocking,
                    FALSE,    /* don't try to open the db yet. */
                    NULL,
                    subpool, subpool));

  if (notify_func)
    {
      /* We notify *twice* here, because there are two different logistical
         actions occuring. */
      svn_repos_notify_t *notify = svn_repos_notify_create(
                                    svn_repos_notify_mutex_acquired, subpool);
      notify_func(notify_baton, notify, subpool);

      notify->action = svn_repos_notify_recover_start;
      notify_func(notify_baton, notify, subpool);
    }

  /* Recover the database to a consistent state. */
  SVN_ERR(svn_fs_recover(repos->db_path, cancel_func, cancel_baton, subpool));

  /* Close shop and free the subpool, to release the exclusive lock. */
  svn_pool_destroy(subpool);

  return SVN_NO_ERROR;
}