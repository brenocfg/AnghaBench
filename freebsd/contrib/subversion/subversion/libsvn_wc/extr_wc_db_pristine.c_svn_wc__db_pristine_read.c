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
struct TYPE_10__ {int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_wc__db_t ;
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_11__ {scalar_t__ kind; } ;
typedef  TYPE_2__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_WC_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_WC__DB_WITH_TXN (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  VERIFY_USABLE_WCROOT (TYPE_1__*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  get_pristine_fname (char const**,int /*<<< orphan*/ ,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pristine_read_txn (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__ const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_checksum_sha1 ; 
 int svn_dirent_is_absolute (char const*) ; 
 int /*<<< orphan*/  svn_dirent_local_style (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_wc__db_wcroot_parse_local_abspath (TYPE_1__**,char const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_wc__db_pristine_read(svn_stream_t **contents,
                         svn_filesize_t *size,
                         svn_wc__db_t *db,
                         const char *wri_abspath,
                         const svn_checksum_t *sha1_checksum,
                         apr_pool_t *result_pool,
                         apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot;
  const char *local_relpath;
  const char *pristine_abspath;

  SVN_ERR_ASSERT(svn_dirent_is_absolute(wri_abspath));

  /* Some 1.6-to-1.7 wc upgrades created rows without checksums and
     updating such a row passes NULL here. */
  if (!sha1_checksum)
    return svn_error_createf(SVN_ERR_WC_CORRUPT, NULL,
                             _("Can't read '%s' from pristine store "
                               "because no checksum supplied"),
                             svn_dirent_local_style(wri_abspath, scratch_pool));

  SVN_ERR_ASSERT(sha1_checksum->kind == svn_checksum_sha1);

  SVN_ERR(svn_wc__db_wcroot_parse_local_abspath(&wcroot, &local_relpath, db,
                              wri_abspath, scratch_pool, scratch_pool));
  VERIFY_USABLE_WCROOT(wcroot);

  SVN_ERR(get_pristine_fname(&pristine_abspath, wcroot->abspath,
                             sha1_checksum,
                             scratch_pool, scratch_pool));
  SVN_WC__DB_WITH_TXN(
    pristine_read_txn(contents, size,
                      wcroot, sha1_checksum, pristine_abspath,
                      result_pool, scratch_pool),
    wcroot);

  return SVN_NO_ERROR;
}