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
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_CONFIG_MULTITHREAD ; 
 int /*<<< orphan*/  SQLITE_ERROR_CODE (int) ; 
 int /*<<< orphan*/  SQLITE_ERR_MSG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SQLITE_MISUSE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SVN_ERR_SQLITE_ERROR ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE_MIN_VERSION ; 
 scalar_t__ SVN_SQLITE_MIN_VERSION_NUMBER ; 
 int /*<<< orphan*/  _ (char*) ; 
 int sqlite3_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_initialize () ; 
 int /*<<< orphan*/  sqlite3_libversion () ; 
 scalar_t__ sqlite3_libversion_number () ; 
 int /*<<< orphan*/  sqlite3_threadsafe () ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static svn_error_t *
init_sqlite(void *baton, apr_pool_t *pool)
{
  if (sqlite3_libversion_number() < SVN_SQLITE_MIN_VERSION_NUMBER)
    {
      return svn_error_createf(
                    SVN_ERR_SQLITE_ERROR, NULL,
                    _("SQLite compiled for %s, but running with %s"),
                    SVN_SQLITE_MIN_VERSION, sqlite3_libversion());
    }

#if APR_HAS_THREADS

  /* SQLite 3.5 allows verification of its thread-safety at runtime.
     Older versions are simply expected to have been configured with
     --enable-threadsafe, which compiles with -DSQLITE_THREADSAFE=1
     (or -DTHREADSAFE, for older versions). */
  if (! sqlite3_threadsafe())
    return svn_error_create(SVN_ERR_SQLITE_ERROR, NULL,
                            _("SQLite is required to be compiled and run in "
                              "thread-safe mode"));

  /* If SQLite has been already initialized, sqlite3_config() returns
     SQLITE_MISUSE. */
  {
    int err = sqlite3_config(SQLITE_CONFIG_MULTITHREAD);
    if (err != SQLITE_OK && err != SQLITE_MISUSE)
      return svn_error_createf(SQLITE_ERROR_CODE(err), NULL,
                               _("Could not configure SQLite [S%d]"), err);
  }
  SQLITE_ERR_MSG(sqlite3_initialize(), _("Could not initialize SQLite"));

#endif /* APR_HAS_THRADS */

  return SVN_NO_ERROR;
}