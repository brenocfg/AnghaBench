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
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_4__ {TYPE_2__* fsap_data; } ;
typedef  TYPE_1__ svn_fs_t ;
typedef  int svn_boolean_t ;
struct TYPE_5__ {scalar_t__ min_unpacked_rev; } ;
typedef  TYPE_2__ fs_fs_data_t ;

/* Variables and functions */

svn_boolean_t
svn_fs_fs__is_packed_rev(svn_fs_t *fs,
                         svn_revnum_t rev)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  return (rev < ffd->min_unpacked_rev);
}