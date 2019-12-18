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
typedef  int svn_boolean_t ;

/* Variables and functions */
 int TRUE ; 
 int svn_cmdline__stdin_is_a_terminal () ; 

svn_boolean_t
svn_cmdline__be_interactive(svn_boolean_t non_interactive,
                            svn_boolean_t force_interactive)
{
  /* If neither --non-interactive nor --force-interactive was passed,
   * be interactive if stdin is a terminal.
   * If --force-interactive was passed, always be interactive. */
  if (!force_interactive && !non_interactive)
    {
      return svn_cmdline__stdin_is_a_terminal();
    }
  else if (force_interactive)
    return TRUE;

  return !non_interactive;
}