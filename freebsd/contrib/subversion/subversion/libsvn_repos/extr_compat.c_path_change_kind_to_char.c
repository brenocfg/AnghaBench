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
typedef  size_t svn_fs_path_change_kind_t ;

/* Variables and functions */
 size_t svn_fs_path_change_modify ; 
 size_t svn_fs_path_change_replace ; 

__attribute__((used)) static char
path_change_kind_to_char(svn_fs_path_change_kind_t kind)
{
  const char symbol[] = "MADR";

  if (kind < svn_fs_path_change_modify || kind > svn_fs_path_change_replace)
    return 0;

  return symbol[kind];
}