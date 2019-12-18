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
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_EXT_PROPS ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 char const* apr_pstrcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_fs_fs__path_txn_node_rev (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

const char *
svn_fs_fs__path_txn_node_props(svn_fs_t *fs,
                               const svn_fs_id_t *id,
                               apr_pool_t *pool)
{
  return apr_pstrcat(pool, svn_fs_fs__path_txn_node_rev(fs, id, pool),
                     PATH_EXT_PROPS, SVN_VA_NULL);
}