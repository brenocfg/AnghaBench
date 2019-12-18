#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_proc; int /*<<< orphan*/  td_name; } ;
struct nosys_args {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int
syscall_not_present(struct thread *td, const char *s, struct nosys_args *uap)
{
	log(LOG_ERR, "cmd %s pid %d tried to use non-present %s\n",
			td->td_name, td->td_proc->p_pid, s);

	/* a " return nosys(p, uap); " here causes a core dump.
	 */

	return ENOSYS;
}