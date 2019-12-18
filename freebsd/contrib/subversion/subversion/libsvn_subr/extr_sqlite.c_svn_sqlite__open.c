#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__mode_t ;
struct TYPE_10__ {char const* const* statement_strings; int nbr_statements; int /*<<< orphan*/ * state_pool; void* prepared_stmts; int /*<<< orphan*/  db3; int /*<<< orphan*/  sqlext_buf3; int /*<<< orphan*/  sqlext_buf2; int /*<<< orphan*/  sqlext_buf1; } ;
typedef  TYPE_1__ svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_int32_t ;

/* Variables and functions */
 int SQLITE_DETERMINISTIC ; 
 int /*<<< orphan*/  SQLITE_ERR_CLOSE (int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SQLITE_TESTCTRL_OPTIMIZATIONS ; 
 int SQLITE_UTF8 ; 
 int STMT_INTERNAL_LAST ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE__ERR_CLOSE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 void* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  apr_pool_cleanup_null ; 
 int /*<<< orphan*/  apr_pool_cleanup_register (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_apr ; 
 int /*<<< orphan*/  collate_ucs_nfd ; 
 int /*<<< orphan*/  exec_sql (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  glob_ucs_nfd ; 
 int /*<<< orphan*/  init_sqlite ; 
 int /*<<< orphan*/  internal_open (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  like_ucs_nfd ; 
 int /*<<< orphan*/  sqlite3_create_collation (int /*<<< orphan*/ ,char*,int,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_create_function (int /*<<< orphan*/ ,char*,int,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sqlite3_libversion_number () ; 
 int /*<<< orphan*/  sqlite3_profile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_sourceid () ; 
 int /*<<< orphan*/  sqlite3_test_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_trace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite_init_state ; 
 int /*<<< orphan*/  sqlite_profiler ; 
 int /*<<< orphan*/  sqlite_tracer ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  svn_atomic__init_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_error_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_membuf__create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_sqlite__open(svn_sqlite__db_t **db, const char *path,
                 svn_sqlite__mode_t mode, const char * const statements[],
                 int unused1, const char * const *unused2,
                 apr_int32_t timeout,
                 apr_pool_t *result_pool, apr_pool_t *scratch_pool)
{
  SVN_ERR(svn_atomic__init_once(&sqlite_init_state,
                                init_sqlite, NULL, scratch_pool));

  *db = apr_pcalloc(result_pool, sizeof(**db));

  SVN_ERR(internal_open(*db, path, mode, timeout, scratch_pool));

#if SQLITE_VERSION_NUMBER >= 3008000 && SQLITE_VERSION_NUMBER < 3009000
  /* disable SQLITE_ENABLE_STAT3/4 from 3.8.1 - 3.8.3 (but not 3.8.3.1+)
   * to prevent using it when it's buggy.
   * See: https://www.sqlite.org/src/info/4c86b126f2 */
  if (sqlite3_libversion_number() > 3008000 &&
      sqlite3_libversion_number() < 3008004 &&
      strcmp(sqlite3_sourceid(),"2014-02-11")<0)
    {
      sqlite3_test_control(SQLITE_TESTCTRL_OPTIMIZATIONS, (*db)->db3, 0x800);
    }
#endif

#ifdef SVN_UNICODE_NORMALIZATION_FIXES
  /* Create extension buffers with space for 200 UCS-4 characters. */
  svn_membuf__create(&(*db)->sqlext_buf1, 800, result_pool);
  svn_membuf__create(&(*db)->sqlext_buf2, 800, result_pool);
  svn_membuf__create(&(*db)->sqlext_buf3, 800, result_pool);

  /* Register collation and LIKE and GLOB operator replacements. */
  SQLITE_ERR_CLOSE(sqlite3_create_collation((*db)->db3,
                                            "svn-ucs-nfd", SQLITE_UTF8,
                                            *db, collate_ucs_nfd),
                   db, scratch_pool);
  /* ### Is it really necessary to override these functions?
         I would assume the default implementation to be collation agnostic?
         And otherwise our implementation should be...

         The default implementation is in some cases index backed, while our
         implementation can't be. With an index based on the collation it could
         be. */
  SQLITE_ERR_CLOSE(sqlite3_create_function((*db)->db3, "glob", 2,
                                           SQLITE_UTF8 | SQLITE_DETERMINISTIC,
                                           *db, glob_ucs_nfd, NULL, NULL),
                   db, scratch_pool);
  SQLITE_ERR_CLOSE(sqlite3_create_function((*db)->db3, "like", 2,
                                           SQLITE_UTF8 | SQLITE_DETERMINISTIC,
                                           *db, like_ucs_nfd, NULL, NULL),
                   db, scratch_pool);
  SQLITE_ERR_CLOSE(sqlite3_create_function((*db)->db3, "like", 3,
                                           SQLITE_UTF8 | SQLITE_DETERMINISTIC,
                                           *db, like_ucs_nfd, NULL, NULL),
                   db, scratch_pool);
#endif /* SVN_UNICODE_NORMALIZATION_FIXES */

#ifdef SQLITE3_DEBUG
  sqlite3_trace((*db)->db3, sqlite_tracer, (*db)->db3);
#endif
#ifdef SQLITE3_PROFILE
  sqlite3_profile((*db)->db3, sqlite_profiler, (*db)->db3);
#endif

  SVN_SQLITE__ERR_CLOSE(exec_sql(*db,
              /* The default behavior of the LIKE operator is to ignore case
                 for ASCII characters. Hence, by default 'a' LIKE 'A' is true.
                 The case_sensitive_like pragma installs a new application-
                 defined LIKE function that is either case sensitive or
                 insensitive depending on the value of the case_sensitive_like
                 pragma. */
              "PRAGMA case_sensitive_like=1;"
              /* Disable synchronization to disable the explicit disk flushes
                 that make Sqlite up to 50 times slower; especially on small
                 transactions.

                 This removes some stability guarantees on specific hardware
                 and power failures, but still guarantees atomic commits on
                 application crashes. With our dependency on external data
                 like pristine files (Wc) and revision files (repository),
                 we can't keep up these additional guarantees anyway.

                 ### Maybe switch to NORMAL(1) when we use larger transaction
                     scopes */
              "PRAGMA synchronous=OFF;"
              /* Enable recursive triggers so that a user trigger will fire
                 in the deletion phase of an INSERT OR REPLACE statement.
                 Requires SQLite >= 3.6.18  */
              "PRAGMA recursive_triggers=ON;"
              /* Enforce current Sqlite default behavior. Some distributions
                 might change the Sqlite defaults without realizing how this
                 affects application(read: Subversion) performance/behavior. */
              "PRAGMA foreign_keys=OFF;"      /* SQLITE_DEFAULT_FOREIGN_KEYS*/
              "PRAGMA locking_mode = NORMAL;" /* SQLITE_DEFAULT_LOCKING_MODE */
              /* Testing shows TRUNCATE is faster than DELETE on Windows. */
              "PRAGMA journal_mode = TRUNCATE;"
              ),
                *db);

#if defined(SVN_DEBUG)
  /* When running in debug mode, enable the checking of foreign key
     constraints.  This has possible performance implications, so we don't
     bother to do it for production...for now. */
  SVN_SQLITE__ERR_CLOSE(exec_sql(*db, "PRAGMA foreign_keys=ON;"),
                        *db);
#endif

#ifdef SVN_SQLITE_REVERSE_UNORDERED_SELECTS
  /* When enabled, this PRAGMA causes SELECT statements without an ORDER BY
     clause to emit their results in the reverse order of what they normally
     would.  This can help detecting invalid assumptions about the result
     order.*/
  SVN_SQLITE__ERR_CLOSE(exec_sql(*db, "PRAGMA reverse_unordered_selects=ON;"),
                        *db);
#endif

  /* Store temporary tables in RAM instead of in temporary files, but don't
     fail on this if this option is disabled in the sqlite compilation by
     setting SQLITE_TEMP_STORE to 0 (always to disk) */
  svn_error_clear(exec_sql(*db, "PRAGMA temp_store = MEMORY;"));

  /* Store the provided statements. */
  if (statements)
    {
      (*db)->statement_strings = statements;
      (*db)->nbr_statements = 0;
      while (*statements != NULL)
        {
          statements++;
          (*db)->nbr_statements++;
        }

      (*db)->prepared_stmts = apr_pcalloc(
                                  result_pool,
                                  ((*db)->nbr_statements + STMT_INTERNAL_LAST)
                                                * sizeof(svn_sqlite__stmt_t *));
    }
  else
    {
      (*db)->nbr_statements = 0;
      (*db)->prepared_stmts = apr_pcalloc(result_pool,
                                          (0 + STMT_INTERNAL_LAST)
                                                * sizeof(svn_sqlite__stmt_t *));
    }

  (*db)->state_pool = result_pool;
  apr_pool_cleanup_register(result_pool, *db, close_apr, apr_pool_cleanup_null);

  return SVN_NO_ERROR;
}