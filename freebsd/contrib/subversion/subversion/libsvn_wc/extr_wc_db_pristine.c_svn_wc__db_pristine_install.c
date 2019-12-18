#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
struct TYPE_11__ {int /*<<< orphan*/  inner_stream; TYPE_1__* wcroot; } ;
typedef  TYPE_2__ svn_wc__db_install_data_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_12__ {scalar_t__ kind; } ;
typedef  TYPE_3__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE__WITH_IMMEDIATE_TXN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pristine_fname (char const**,int /*<<< orphan*/ ,TYPE_3__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pristine_install_txn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,TYPE_3__ const*,TYPE_3__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_checksum_md5 ; 
 scalar_t__ svn_checksum_sha1 ; 

svn_error_t *
svn_wc__db_pristine_install(svn_wc__db_install_data_t *install_data,
                            const svn_checksum_t *sha1_checksum,
                            const svn_checksum_t *md5_checksum,
                            apr_pool_t *scratch_pool)
{
  svn_wc__db_wcroot_t *wcroot = install_data->wcroot;
  const char *pristine_abspath;

  SVN_ERR_ASSERT(sha1_checksum != NULL);
  SVN_ERR_ASSERT(sha1_checksum->kind == svn_checksum_sha1);
  SVN_ERR_ASSERT(md5_checksum != NULL);
  SVN_ERR_ASSERT(md5_checksum->kind == svn_checksum_md5);

  SVN_ERR(get_pristine_fname(&pristine_abspath, wcroot->abspath,
                             sha1_checksum,
                             scratch_pool, scratch_pool));

  /* Ensure the SQL txn has at least a 'RESERVED' lock before we start looking
   * at the disk, to ensure no concurrent pristine install/delete txn. */
  SVN_SQLITE__WITH_IMMEDIATE_TXN(
    pristine_install_txn(wcroot->sdb,
                         install_data->inner_stream, pristine_abspath,
                         sha1_checksum, md5_checksum,
                         scratch_pool),
    wcroot->sdb);

  return SVN_NO_ERROR;
}