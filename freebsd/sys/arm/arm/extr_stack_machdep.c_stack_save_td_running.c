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
struct thread {int dummy; } ;
struct stack {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  stack_save (struct stack*) ; 

int
stack_save_td_running(struct stack *st, struct thread *td)
{

	if (td == curthread) {
		stack_save(st);
		return (0);
	}
	return (EOPNOTSUPP);
}