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
#define  TODO_EDIT 133 
#define  TODO_FIXUP 132 
#define  TODO_PICK 131 
#define  TODO_REVERT 130 
#define  TODO_REWORD 129 
#define  TODO_SQUASH 128 

__attribute__((used)) static int is_pick_or_similar(enum todo_command command)
{
	switch (command) {
	case TODO_PICK:
	case TODO_REVERT:
	case TODO_EDIT:
	case TODO_REWORD:
	case TODO_FIXUP:
	case TODO_SQUASH:
		return 1;
	default:
		return 0;
	}
}