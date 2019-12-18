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

/* Variables and functions */
 int /*<<< orphan*/  enable_overlay_breakpoints () ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  overlay_debugging ; 
 int /*<<< orphan*/  ovly_auto ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 

__attribute__((used)) static void
overlay_auto_command (char *args, int from_tty)
{
  overlay_debugging = ovly_auto;
  enable_overlay_breakpoints ();
  if (info_verbose)
    printf_unfiltered ("Automatic overlay debugging enabled.");
}