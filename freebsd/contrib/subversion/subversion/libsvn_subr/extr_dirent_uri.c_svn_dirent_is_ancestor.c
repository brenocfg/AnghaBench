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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/ * svn_dirent_skip_ancestor (char const*,char const*) ; 

svn_boolean_t
svn_dirent_is_ancestor(const char *parent_dirent, const char *child_dirent)
{
  return svn_dirent_skip_ancestor(parent_dirent, child_dirent) != NULL;
}