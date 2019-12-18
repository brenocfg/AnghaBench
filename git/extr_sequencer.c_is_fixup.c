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
typedef  enum todo_command { ____Placeholder_todo_command } todo_command ;

/* Variables and functions */
 int TODO_FIXUP ; 
 int TODO_SQUASH ; 

__attribute__((used)) static int is_fixup(enum todo_command command)
{
	return command == TODO_FIXUP || command == TODO_SQUASH;
}