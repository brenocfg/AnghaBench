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
 int /*<<< orphan*/  monitor_open (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rom68k_cmds ; 

__attribute__((used)) static void
rom68k_open (char *args, int from_tty)
{
  monitor_open (args, &rom68k_cmds, from_tty);
}