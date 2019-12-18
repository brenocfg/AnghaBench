#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sdb; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_sqlite__stmt_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_LOOK_FOR_WORK ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  pristine_remove_if_unreferenced (TYPE_1__*,TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_checksum_sha1 ; 
 int svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_sqlite__get_statement (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_sqlite__reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_sqlite__step (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_pristine_get_sha1 (TYPE_2__ const**,int /*<<< orphan*/ *,char const*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_pristine_remove(svn_wc__db_t *db,
                           const char *wri_abspath,
                           const svn_checksum_t *sha1_checksum,
                           apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(wri_abspath));
  SVN_ERR_ASSERT(sha1_checksum != NULL);
  /* ### Transitional: accept MD-5 and look up the SHA-1.  Return an error
   * if the pristine text is not in the store. */
  if (sha1_checksum->kind != svn_checksum_sha1)
    SVN_ERR(svn_wc__db_pristine_get_sha1(&sha1_checksum, db, wri_abspath,
                                         sha1_checksum,
                                         scratch_pool, scratch_pool));
  SVN_ERR_ASSERT(sha1_checksum->kind == svn_checksum_sha1);

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              wri_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  /* If the work queue is not empty, don't delete any pristine text because
   * the work queue may contain a reference to it. */
  {
    svn_sqlite__stmt_t *stmt;
    svn_boolean_t have_row;

    SVN_ERR(svn_sqlite__get_statement(&stmt, wcroot->sdb, STMT_LOOK_FOR_WORK));
    SVN_ERR(svn_sqlite__step(&have_row, stmt));
    SVN_ERR(svn_sqlite__reset(stmt));

    if (have_row)
      return SVN_NO_ERROR;
  }

  /* If not referenced, remove the PRISTINE table row and the file. */
  SVN_ERR(pristine_remove_if_unreferenced(wcroot, sha1_checksum, scratch_pool));

  return SVN_NO_ERROR;
}