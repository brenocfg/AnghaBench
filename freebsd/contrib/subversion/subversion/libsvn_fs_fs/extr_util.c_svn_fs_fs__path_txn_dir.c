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
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_fs__id_part_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_EXT_TXN ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT_NO_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  combine_txn_id_string (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char const* svn_dirent_join (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txns_dir (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const char *
svn_fs_fs__path_txn_dir(svn_fs_t *fs,
                        const svn_fs_fs__id_part_t *txn_id,
                        apr_pool_t *pool)
{
  SVN_ERR_ASSERT_NO_RETURN(txn_id != NULL);
  return svn_dirent_join(svn_fs_fs__path_txns_dir(fs, pool),
                         combine_txn_id_string(txn_id, PATH_EXT_TXN, pool),
                         pool);
}