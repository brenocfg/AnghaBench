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
typedef  int svn_depth_t ;

/* Variables and functions */
#define  svn_depth_empty 133 
#define  svn_depth_exclude 132 
#define  svn_depth_files 131 
#define  svn_depth_immediates 130 
#define  svn_depth_infinity 129 
#define  svn_depth_unknown 128 

const char *
svn_depth_to_word(svn_depth_t depth)
{
  switch (depth)
    {
    case svn_depth_exclude:
      return "exclude";
    case svn_depth_unknown:
      return "unknown";
    case svn_depth_empty:
      return "empty";
    case svn_depth_files:
      return "files";
    case svn_depth_immediates:
      return "immediates";
    case svn_depth_infinity:
      return "infinity";
    default:
      return "INVALID-DEPTH";
    }
}