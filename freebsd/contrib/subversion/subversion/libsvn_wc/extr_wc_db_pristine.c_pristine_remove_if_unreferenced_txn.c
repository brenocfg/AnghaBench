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
typedef  int /*<<< orphan*/  svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STMT_DELETE_PRISTINE_IF_UNREFERENCED ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  svn_io_remove_file2 (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_checksum (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__update (int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
pristine_remove_if_unreferenced_txn(svn_sqlite__db_t *sdb,
                                    svn_wc__db_wcroot_t *wcroot,
                                    const svn_checksum_t *sha1_checksum,
                                    const char *pristine_abspath,
                                    apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  int affected_rows;

  /* Remove the DB row, if refcount is 0. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, sdb,
                                    STMT_DELETE_PRISTINE_IF_UNREFERENCED));
  SVN_ERR(svn_sqlite__bind_checksum(stmt, 1, sha1_checksum, scratch_pool));
  SVN_ERR(svn_sqlite__update(&affected_rows, stmt));

  /* If we removed the DB row, then remove the file. */
  if (affected_rows > 0)
    {
      /* If the file is not present, something has gone wrong, but at this
       * point it no longer matters.  In a debug build, raise an error, but
       * in a release build, it is more helpful to ignore it and continue. */
#ifdef SVN_DEBUG
      svn_boolean_t ignore_enoent = FALSE;
#else
      svn_boolean_t ignore_enoent = TRUE;
#endif

      SVN_ERR(svn_io_remove_file2(pristine_abspath, ignore_enoent,
                                  scratch_pool));
    }

  return SVN_NO_ERROR;
}