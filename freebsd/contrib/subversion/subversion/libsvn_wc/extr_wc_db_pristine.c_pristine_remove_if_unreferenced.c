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
struct TYPE_4__ {int /*<<< orphan*/  sdb; int /*<<< orphan*/  abspath; } ;
typedef  TYPE_1__ svn_wc__db_wcroot_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_SQLITE__WITH_IMMEDIATE_TXN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_pristine_fname (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pristine_remove_if_unreferenced_txn (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
pristine_remove_if_unreferenced(svn_wc__db_wcroot_t *wcroot,
                                const svn_checksum_t *sha1_checksum,
                                apr_pool_t *scratch_pool)
{
  const char *pristine_abspath;

  SVN_ERR(get_pristine_fname(&pristine_abspath, wcroot->abspath,
                             sha1_checksum, scratch_pool, scratch_pool));

  /* Ensure the SQL txn has at least a 'RESERVED' lock before we start looking
   * at the disk, to ensure no concurrent pristine install/delete txn. */
  SVN_SQLITE__WITH_IMMEDIATE_TXN(
    pristine_remove_if_unreferenced_txn(
      wcroot->sdb, wcroot, sha1_checksum, pristine_abspath, scratch_pool),
    wcroot->sdb);

  return SVN_NO_ERROR;
}