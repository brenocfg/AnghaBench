#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
struct TYPE_5__ {int /*<<< orphan*/ * txn_dir_cache; } ;
typedef  TYPE_2__ fs_fs_data_t ;

/* Variables and functions */

void
svn_fs_fs__reset_txn_caches(svn_fs_t *fs)
{
  /* we can always just reset the caches. This may degrade performance but
   * can never cause in incorrect behavior. */

  fs_fs_data_t *ffd = fs->fsap_data;
  ffd->txn_dir_cache = NULL;
}