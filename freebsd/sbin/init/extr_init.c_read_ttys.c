#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ttyent {int dummy; } ;
typedef  int /*<<< orphan*/  state_func_t ;
struct TYPE_6__ {struct TYPE_6__* se_next; } ;
typedef  TYPE_1__ session_t ;

/* Variables and functions */
 int /*<<< orphan*/  endttyent () ; 
 int /*<<< orphan*/  free_session (TYPE_1__*) ; 
 struct ttyent* getttyent () ; 
 int /*<<< orphan*/  multi_user ; 
 TYPE_1__* new_session (TYPE_1__*,struct ttyent*) ; 
 TYPE_1__* sessions ; 
 int /*<<< orphan*/  single_user ; 
 scalar_t__ start_session_db () ; 

__attribute__((used)) static state_func_t
read_ttys(void)
{
	session_t *sp, *snext;
	struct ttyent *typ;

	/*
	 * Destroy any previous session state.
	 * There shouldn't be any, but just in case...
	 */
	for (sp = sessions; sp; sp = snext) {
		snext = sp->se_next;
		free_session(sp);
	}
	sessions = 0;
	if (start_session_db())
		return (state_func_t) single_user;

	/*
	 * Allocate a session entry for each active port.
	 * Note that sp starts at 0.
	 */
	while ((typ = getttyent()) != NULL)
		if ((snext = new_session(sp, typ)) != NULL)
			sp = snext;

	endttyent();

	return (state_func_t) multi_user;
}