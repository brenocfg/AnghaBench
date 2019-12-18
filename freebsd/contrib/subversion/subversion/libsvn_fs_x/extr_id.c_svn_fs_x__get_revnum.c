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
typedef  int /*<<< orphan*/  svn_revnum_t ;
typedef  scalar_t__ svn_fs_x__change_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ svn_fs_x__is_revision (scalar_t__) ; 

svn_revnum_t
svn_fs_x__get_revnum(svn_fs_x__change_set_t change_set)
{
  return svn_fs_x__is_revision(change_set)
       ? (svn_revnum_t)change_set
       : SVN_INVALID_REVNUM;
}