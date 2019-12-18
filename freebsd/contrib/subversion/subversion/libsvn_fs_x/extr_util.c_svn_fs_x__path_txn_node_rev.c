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
typedef  int /*<<< orphan*/  svn_fs_x__id_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 char const* construct_txn_node_path (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

const char *
svn_fs_x__path_txn_node_rev(svn_fs_t *fs,
                            const svn_fs_x__id_t *id,
                            apr_pool_t *result_pool,
                            apr_pool_t *scratch_pool)
{
  return construct_txn_node_path(fs, id, "", result_pool, scratch_pool);
}