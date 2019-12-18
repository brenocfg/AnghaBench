#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  path; TYPE_3__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_13__ {int /*<<< orphan*/  apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
struct TYPE_14__ {scalar_t__ format; int /*<<< orphan*/ * rep_cache_db; } ;
typedef  TYPE_3__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_STATUS_IS_EEXIST (int /*<<< orphan*/ ) ; 
 int STMT_CREATE_SCHEMA_V1 ; 
 int STMT_CREATE_SCHEMA_V2 ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ SVN_FS_FS__MIN_REP_CACHE_SCHEMA_V2_FORMAT ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE__ERR_CLOSE (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* path_rep_cache_db (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  statements ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 int /*<<< orphan*/  svn_fs_fs__exists_rep_cache (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* svn_fs_fs__path_current (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_copy_perms (char const*,char const*,int /*<<< orphan*/ *) ; 
 TYPE_2__* svn_io_file_create_empty (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__exec_statements (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_sqlite__mode_rwcreate ; 
 int /*<<< orphan*/  svn_sqlite__open (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__read_schema_version (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
open_rep_cache(void *baton,
               apr_pool_t *pool)
{
  svn_fs_t *fs = baton;
  fs_fs_data_t *ffd = fs->fsap_data;
  svn_sqlite__db_t *sdb;
  const char *db_path;
  int version;

  /* Open (or create) the sqlite database.  It will be automatically
     closed when fs->pool is destroyed. */
  db_path = path_rep_cache_db(fs->path, pool);
#ifndef WIN32
  {
    /* We want to extend the permissions that apply to the repository
       as a whole when creating a new rep cache and not simply default
       to umask. */
    svn_boolean_t exists;

    SVN_ERR(svn_fs_fs__exists_rep_cache(&exists, fs, pool));
    if (!exists)
      {
        const char *current = svn_fs_fs__path_current(fs, pool);
        svn_error_t *err = svn_io_file_create_empty(db_path, pool);

        if (err && !APR_STATUS_IS_EEXIST(err->apr_err))
          /* A real error. */
          return svn_error_trace(err);
        else if (err)
          /* Some other thread/process created the file. */
          svn_error_clear(err);
        else
          /* We created the file. */
          SVN_ERR(svn_io_copy_perms(current, db_path, pool));
      }
  }
#endif
  SVN_ERR(svn_sqlite__open(&sdb, db_path,
                           svn_sqlite__mode_rwcreate, statements,
                           0, NULL, 0,
                           fs->pool, pool));

  SVN_SQLITE__ERR_CLOSE(svn_sqlite__read_schema_version(&version, sdb, pool),
                        sdb);
  /* If we have an uninitialized database, go ahead and create the schema. */
  if (version <= 0)
    {
      int stmt;

      if (ffd->format >= SVN_FS_FS__MIN_REP_CACHE_SCHEMA_V2_FORMAT)
        stmt = STMT_CREATE_SCHEMA_V2;
      else
        stmt = STMT_CREATE_SCHEMA_V1;

      SVN_SQLITE__ERR_CLOSE(svn_sqlite__exec_statements(sdb, stmt), sdb);
    }

  /* This is used as a flag that the database is available so don't
     set it earlier. */
  ffd->rep_cache_db = sdb;

  return SVN_NO_ERROR;
}