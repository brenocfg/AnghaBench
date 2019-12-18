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
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_overlay_update (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
overlay_load_command (char *args, int from_tty)
{
  if (target_overlay_update)
    (*target_overlay_update) (NULL);
  else
    error ("This target does not know how to read its overlay state.");
}