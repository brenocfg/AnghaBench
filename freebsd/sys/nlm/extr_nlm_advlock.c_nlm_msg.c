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
struct thread {struct proc* td_proc; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  tprintf (struct proc*,int /*<<< orphan*/ ,char*,char const*,char const*,...) ; 

__attribute__((used)) static int
nlm_msg(struct thread *td, const char *server, const char *msg, int error)
{
	struct proc *p;

	p = td ? td->td_proc : NULL;
	if (error) {
		tprintf(p, LOG_INFO, "nfs server %s: %s, error %d\n", server,
		    msg, error);
	} else {
		tprintf(p, LOG_INFO, "nfs server %s: %s\n", server, msg);
	}
	return (0);
}