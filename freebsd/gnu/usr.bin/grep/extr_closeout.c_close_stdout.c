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
 int /*<<< orphan*/  close_stdout_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_exit_status ; 

void
close_stdout (void)
{
  close_stdout_status (default_exit_status);
}