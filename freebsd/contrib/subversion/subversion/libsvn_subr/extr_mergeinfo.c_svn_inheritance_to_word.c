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
typedef  int svn_mergeinfo_inheritance_t ;

/* Variables and functions */
#define  svn_mergeinfo_inherited 129 
#define  svn_mergeinfo_nearest_ancestor 128 

const char *
svn_inheritance_to_word(svn_mergeinfo_inheritance_t inherit)
{
  switch (inherit)
    {
    case svn_mergeinfo_inherited:
      return "inherited";
    case svn_mergeinfo_nearest_ancestor:
      return "nearest-ancestor";
    default:
      return "explicit";
    }
}