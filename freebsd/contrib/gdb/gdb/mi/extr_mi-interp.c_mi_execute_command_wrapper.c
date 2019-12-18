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
 scalar_t__ instream ; 
 int /*<<< orphan*/  mi_execute_command (char*,int) ; 
 scalar_t__ stdin ; 

__attribute__((used)) static void
mi_execute_command_wrapper (char *cmd)
{
  mi_execute_command (cmd, stdin == instream);
}