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
typedef  int svn_node_kind_t ;

/* Variables and functions */
#define  svn_node_dir 132 
#define  svn_node_file 131 
#define  svn_node_none 130 
#define  svn_node_symlink 129 
#define  svn_node_unknown 128 

const char *
svn_node_kind_to_word(svn_node_kind_t kind)
{
  switch (kind)
    {
    case svn_node_none:
      return "none";
    case svn_node_file:
      return "file";
    case svn_node_dir:
      return "dir";
    case svn_node_symlink:
      return "symlink";
    case svn_node_unknown:
    default:
      return "unknown";
    }
}