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
struct dirTodoNode {struct dirTodoNode* next; } ;

/* Variables and functions */
 struct dirTodoNode* freedt ; 
 struct dirTodoNode* malloc (int) ; 

__attribute__((used)) static struct dirTodoNode *
newDirTodo(void)
{
	struct dirTodoNode *dt;

	if (!(dt = freedt)) {
		if (!(dt = malloc(sizeof *dt)))
			return 0;
	} else
		freedt = dt->next;
	return dt;
}