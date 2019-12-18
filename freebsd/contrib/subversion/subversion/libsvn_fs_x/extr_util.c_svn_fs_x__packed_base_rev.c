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
typedef  int svn_revnum_t ;
struct TYPE_4__ {int min_unpacked_rev; int max_files_per_dir; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
struct TYPE_5__ {TYPE_1__* fsap_data; } ;
typedef  TYPE_2__ svn_fs_t ;

/* Variables and functions */

svn_revnum_t
svn_fs_x__packed_base_rev(svn_fs_t *fs, svn_revnum_t rev)
{
  svn_fs_x__data_t *ffd = fs->fsap_data;

  return rev < ffd->min_unpacked_rev
       ? rev - (rev % ffd->max_files_per_dir)
       : rev;
}