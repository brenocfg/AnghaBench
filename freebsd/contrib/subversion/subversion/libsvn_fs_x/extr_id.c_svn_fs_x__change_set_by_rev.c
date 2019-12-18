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
typedef  scalar_t__ svn_revnum_t ;
typedef  scalar_t__ svn_fs_x__change_set_t ;

/* Variables and functions */
 scalar_t__ SVN_FS_X__INVALID_CHANGE_SET ; 
 int /*<<< orphan*/  assert (int) ; 

svn_fs_x__change_set_t
svn_fs_x__change_set_by_rev(svn_revnum_t revnum)
{
  assert(revnum >= SVN_FS_X__INVALID_CHANGE_SET);
  return revnum;
}