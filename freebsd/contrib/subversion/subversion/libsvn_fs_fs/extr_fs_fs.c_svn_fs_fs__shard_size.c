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
struct TYPE_5__ {int max_files_per_dir; } ;
typedef  TYPE_2__ fs_fs_data_t ;

/* Variables and functions */

int
svn_fs_fs__shard_size(svn_fs_t *fs)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  return ffd->max_files_per_dir;
}