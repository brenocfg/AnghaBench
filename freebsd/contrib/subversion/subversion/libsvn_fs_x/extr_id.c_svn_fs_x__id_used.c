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
struct TYPE_3__ {scalar_t__ change_set; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 scalar_t__ SVN_FS_X__INVALID_CHANGE_SET ; 

svn_boolean_t
svn_fs_x__id_used(const svn_fs_x__id_t *part)
{
  return part->change_set != SVN_FS_X__INVALID_CHANGE_SET;
}