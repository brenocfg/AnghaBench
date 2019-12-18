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
struct TYPE_5__ {scalar_t__ min_unpacked_rev; scalar_t__ format; } ;
typedef  TYPE_2__ fs_fs_data_t ;

/* Variables and functions */
 scalar_t__ SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT ; 

svn_boolean_t
svn_fs_fs__is_packed_revprop(svn_fs_t *fs,
                             svn_revnum_t rev)
{
  fs_fs_data_t *ffd = fs->fsap_data;

  /* rev 0 will not be packed */
  return (rev < ffd->min_unpacked_rev)
      && (rev != 0)
      && (ffd->format >= SVN_FS_FS__MIN_PACKED_REVPROP_FORMAT);
}