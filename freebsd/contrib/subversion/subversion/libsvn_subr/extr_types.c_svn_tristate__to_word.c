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
typedef  int svn_tristate_t ;

/* Variables and functions */
#define  svn_tristate_false 130 
#define  svn_tristate_true 129 
#define  svn_tristate_unknown 128 

const char *
svn_tristate__to_word(svn_tristate_t tristate)
{
  switch (tristate)
    {
      case svn_tristate_false:
        return "false";
      case svn_tristate_true:
        return "true";
      case svn_tristate_unknown:
      default:
        return NULL;
    }
}