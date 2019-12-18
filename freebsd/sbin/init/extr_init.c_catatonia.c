#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  state_func_t ;
struct TYPE_3__ {int /*<<< orphan*/  se_flags; struct TYPE_3__* se_next; } ;
typedef  TYPE_1__ session_t ;

/* Variables and functions */
 int /*<<< orphan*/  SE_SHUTDOWN ; 
 int /*<<< orphan*/  multi_user ; 
 TYPE_1__* sessions ; 

__attribute__((used)) static state_func_t
catatonia(void)
{
	session_t *sp;

	for (sp = sessions; sp; sp = sp->se_next)
		sp->se_flags |= SE_SHUTDOWN;

	return (state_func_t) multi_user;
}