#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  scalar_t__ svn_node_kind_t ;
struct TYPE_16__ {scalar_t__ apr_err; } ;
typedef  TYPE_2__ svn_error_t ;
struct TYPE_17__ {scalar_t__ kind; } ;
typedef  TYPE_3__ svn_checksum_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_FROM_OS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STMT_SELECT_PRISTINE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_2__* SVN_NO_ERROR ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  get_pristine_fname (char const**,int /*<<< orphan*/ ,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_error_clear (TYPE_2__*) ; 
 TYPE_2__* svn_error_trace (TYPE_2__*) ; 
 TYPE_2__* svn_io_check_path (char const*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_node_file ; 
 int /*<<< orphan*/  svn_sqlite__bind_checksum (int /*<<< orphan*/ *,int,TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_pristine_check(svn_boolean_t *present,
                          svn_wc__db_t *db,
                          const char *wri_abspath,
                          const svn_checksum_t *sha1_checksum,
                          apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  svn_sqlite__stmt_t *stmt;
  svn_boolean_t have_row;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(wri_abspath));
  SVN_ERR_ASSERT(sha1_checksum != NULL);

  if (sha1_checksum->kind != svn_checksum_sha1)
    {
      *present = FALSE;
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              wri_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  /* A filestat is much cheaper than a sqlite transaction especially on NFS,
     so first check if there is a pristine file and then if we are allowed
     to use it. */
  {
    const char *pristine_abspath;
    svn_node_kind_t kind_on_disk;
    svn_error_t *err;

    SVN_ERR(get_pristine_fname(&pristine_abspath, wcroot->abspath,
                               sha1_checksum, scratch_pool, scratch_pool));
    err = svn_io_check_path(pristine_abspath, &kind_on_disk, scratch_pool);
#ifdef WIN32
    if (err && err->apr_err == APR_FROM_OS_ERROR(ERROR_ACCESS_DENIED))
      {
        svn_error_clear(err);
        /* Possible race condition: The filename is locked, but there is no
           file or dir with this name. Let's fall back on checking the DB.

           This case is triggered by the pristine store tests on deleting
           a file that is still open via another handle, where this other
           handle has a FILE_SHARE_DELETE share mode.
         */
      }
    else
#endif
    if (err)
      return svn_error_trace(err);
    else if (kind_on_disk != svn_node_file)
      {
        *present = FALSE;
        return SVN_NO_ERROR;
      }
  }

  /* Check that there is an entry in the PRISTINE table. */
  SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb, STMT_SELECT_PRISTINE));
  SVN_ERR(svn_sqlite__bind_checksum(stmt, 1, sha1_checksum, scratch_pool));
  SVN_ERR(svn_sqlite__step(&have_row, stmt));
  SVN_ERR(svn_sqlite__reset(stmt));

  *present = have_row;
  return SVN_NO_ERROR;
}