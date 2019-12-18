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
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  create_db_logs_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_io_file_lock2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* svn_repos_db_logs_lockfile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
lock_db_logs_file(svn_repos_t *repos,
                  svn_boolean_t exclusive,
                  apr_pool_t *pool)
{
  const char * lock_file = svn_repos_db_logs_lockfile(repos, pool);

  /* Try to create a lock file, in case if it is missing. As in case of the
     repositories created before hotcopy functionality.  */
  svn_error_clear(create_db_logs_lock(repos, pool));

  return svn_io_file_lock2(lock_file, exclusive, FALSE, pool);
}