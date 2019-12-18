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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  bdb_env_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int DB_RECOVER ; 
 int DB_RECOVER_FATAL ; 
 int SVN_BDB_PRIVATE_ENV_FLAGS ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_fs_bdb__close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_bdb__open (int /*<<< orphan*/ **,char const*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
bdb_recover(const char *path, svn_boolean_t fatal, apr_pool_t *pool)
{
  bdb_env_baton_t *bdb;

  /* Here's the comment copied from db_recover.c:

     Initialize the environment -- we don't actually do anything
     else, that all that's needed to run recovery.

     Note that we specify a private environment, as we're about to
     create a region, and we don't want to leave it around.  If we
     leave the region around, the application that should create it
     will simply join it instead, and will then be running with
     incorrectly sized (and probably terribly small) caches.  */

  /* Note that since we're using a private environment, we shoudl
     /not/ initialize locking. We want the environment files to go
     away. */

  SVN_ERR(svn_fs_bdb__open(&bdb, path,
                           ((fatal ? DB_RECOVER_FATAL : DB_RECOVER)
                            | SVN_BDB_PRIVATE_ENV_FLAGS),
                           0666, pool));
  return svn_fs_bdb__close(bdb);
}