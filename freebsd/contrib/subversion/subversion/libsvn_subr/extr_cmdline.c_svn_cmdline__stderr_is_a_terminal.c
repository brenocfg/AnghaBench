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
 int /*<<< orphan*/  STDERR_FILENO ; 
 scalar_t__ _isatty (int /*<<< orphan*/ ) ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 

svn_boolean_t
svn_cmdline__stderr_is_a_terminal(void)
{
#ifdef WIN32
  return (_isatty(STDERR_FILENO) != 0);
#else
  return (isatty(STDERR_FILENO) != 0);
#endif
}