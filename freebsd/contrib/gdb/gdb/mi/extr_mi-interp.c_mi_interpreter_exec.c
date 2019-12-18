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
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  mi_execute_command_wrapper (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int
mi_interpreter_exec (void *data, const char *command)
{
  char *tmp = alloca (strlen (command) + 1);
  strcpy (tmp, command);
  mi_execute_command_wrapper (tmp);
  return 1;
}