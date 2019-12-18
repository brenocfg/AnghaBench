#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_x__txn_id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
struct TYPE_3__ {unsigned char const* digest; int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ svn_checksum_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_checksum_sha1 ; 
 int /*<<< orphan*/  svn_checksum_to_cstring (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__path_txn_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
svn_fs_x__path_txn_sha1(svn_fs_t *fs,
                        svn_fs_x__txn_id_t txn_id,
                        const unsigned char *sha1,
                        apr_pool_t *pool)
{
  svn_checksum_t checksum;
  checksum.digest = sha1;
  checksum.kind = svn_checksum_sha1;

  return svn_dirent_join(svn_fs_x__path_txn_dir(fs, txn_id, pool),
                         svn_checksum_to_cstring(&checksum, pool),
                         pool);
}