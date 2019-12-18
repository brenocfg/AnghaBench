#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  rev; TYPE_1__* fs; TYPE_3__* fsap_data; scalar_t__ is_txn_root; } ;
typedef  TYPE_2__ svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_cache__t ;
struct TYPE_8__ {int /*<<< orphan*/ * txn_node_cache; } ;
typedef  TYPE_3__ fs_txn_root_data_t ;
struct TYPE_9__ {int /*<<< orphan*/ * rev_node_cache; } ;
typedef  TYPE_4__ fs_fs_data_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
struct TYPE_6__ {TYPE_4__* fsap_data; } ;

/* Variables and functions */
 char* svn_fs_fs__combine_number_and_string (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
locate_cache(svn_cache__t **cache,
             const char **key,
             svn_fs_root_t *root,
             const char *path,
             apr_pool_t *pool)
{
  if (root->is_txn_root)
    {
      fs_txn_root_data_t *frd = root->fsap_data;

      if (cache)
        *cache = frd->txn_node_cache;
      if (key && path)
        *key = path;
    }
  else
    {
      fs_fs_data_t *ffd = root->fs->fsap_data;

      if (cache)
        *cache = ffd->rev_node_cache;
      if (key && path)
        *key = svn_fs_fs__combine_number_and_string(root->rev, path, pool);
    }
}