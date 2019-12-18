#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_sqlite__db_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_4__ {scalar_t__ size; } ;
typedef  TYPE_1__ apr_finfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  APR_FINFO_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STMT_INSERT_PRISTINE ; 
 int /*<<< orphan*/  STMT_SELECT_PRISTINE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT_TEXT_BASE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  apr_off_t_toa (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  svn_checksum_to_cstring_display (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_io_set_file_read_only (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_io_stat (TYPE_1__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_checksum (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__bind_int64 (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream__install_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream__install_get_info (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream__install_stream (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
pristine_install_txn(svn_sqlite__db_t *sdb,
                     /* The path to the source file that is to be moved into place. */
                     svn_stream_t *install_stream,
                     /* The target path for the file (within the pristine store). */
                     const char *pristine_abspath,
                     /* The pristine text's SHA-1 checksum. */
                     const svn_checksum_t *sha1_checksum,
                     /* The pristine text's MD-5 checksum. */
                     const svn_checksum_t *md5_checksum,
                     apr_pool_t *scratch_pool)
{
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;

  /* If this pristine text is already present in the store, just keep it:
   * delete the new one and return. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, sdb, STMT_SELECT_PRISTINE));
  SVN_ERR(svn_sqlite__bind_checksum(stmt, 1, sha1_checksum, scratch_pool));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  SVN_ERR(svn_sqlite__reset(stmt));

  if (have_row)
    {
#ifdef SVN_DEBUG
      /* Consistency checks.  Verify both files exist and match.
       * ### We could check much more. */
      {
        apr_finfo_t finfo1, finfo2;

        SVN_ERR(svn_stream__install_get_info(&finfo1, install_stream, APR_FINFO_SIZE,
                                             scratch_pool));

        SVN_ERR(svn_io_stat(&finfo2, pristine_abspath, APR_FINFO_SIZE,
                            scratch_pool));
        if (finfo1.size != finfo2.size)
          {
            return svn_error_createf(
              SVN_ERR_WC_CORRUPT_TEXT_BASE, NULL,
              _("New pristine text '%s' has different size: %s versus %s"),
              svn_checksum_to_cstring_display(sha1_checksum, scratch_pool),
              apr_off_t_toa(scratch_pool, finfo1.size),
              apr_off_t_toa(scratch_pool, finfo2.size));
          }
      }
#endif

      /* Remove the temp file: it's already there */
      SVN_ERR(svn_stream__install_delete(install_stream, scratch_pool));
      return SVN_NO_ERROR;
    }

  /* Move the file to its target location.  (If it is already there, it is
   * an orphan file and it doesn't matter if we overwrite it.) */
  {
    apr_finfo_t finfo;
    SVN_ERR(svn_stream__install_get_info(&finfo, install_stream,
                                         APR_FINFO_SIZE, scratch_pool));
    SVN_ERR(svn_stream__install_stream(install_stream, pristine_abspath,
                                       TRUE, scratch_pool));

    SVN_ERR(svn_sqlite__get_statement(&stmt, sdb, STMT_INSERT_PRISTINE));
    SVN_ERR(svn_sqlite__bind_checksum(stmt, 1, sha1_checksum, scratch_pool));
    SVN_ERR(svn_sqlite__bind_checksum(stmt, 2, md5_checksum, scratch_pool));
    SVN_ERR(svn_sqlite__bind_int64(stmt, 3, finfo.size));
    SVN_ERR(svn_sqlite__insert(NULL, stmt));

    SVN_ERR(svn_io_set_file_read_only(pristine_abspath, FALSE, scratch_pool));
  }

  return SVN_NO_ERROR;
}