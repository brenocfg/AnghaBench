#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock_path; } ;
typedef  TYPE_1__ svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_W (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  create_db_lock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_db_logs_lock (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_repos_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
create_locks(svn_repos_t *repos, apr_pool_t *pool)
{
  /* Create the locks directory. */
  SVN_ERR_W(create_repos_dir(repos->lock_path, pool),
            _("Creating lock dir"));

  SVN_ERR(create_db_lock(repos, pool));
  return create_db_logs_lock(repos, pool);
}