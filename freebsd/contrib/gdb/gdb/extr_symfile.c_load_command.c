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
 char* get_exec_file (int) ; 
 int overlay_cache_invalid ; 
 int /*<<< orphan*/  target_load (char*,int) ; 

__attribute__((used)) static void
load_command (char *arg, int from_tty)
{
  if (arg == NULL)
    arg = get_exec_file (1);
  target_load (arg, from_tty);

  /* After re-loading the executable, we don't really know which
     overlays are mapped any more.  */
  overlay_cache_invalid = 1;
}