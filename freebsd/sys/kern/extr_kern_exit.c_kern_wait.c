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
struct rusage {int dummy; } ;
struct __wrusage {struct rusage wru_self; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  idtype_t ;
typedef  scalar_t__ id_t ;

/* Variables and functions */
 int /*<<< orphan*/  P_ALL ; 
 int /*<<< orphan*/  P_PGID ; 
 int /*<<< orphan*/  P_PID ; 
 scalar_t__ WAIT_ANY ; 
 int WEXITED ; 
 int WTRAPPED ; 
 int kern_wait6 (struct thread*,int /*<<< orphan*/ ,scalar_t__,int*,int,struct __wrusage*,int /*<<< orphan*/ *) ; 

int
kern_wait(struct thread *td, pid_t pid, int *status, int options,
    struct rusage *rusage)
{
	struct __wrusage wru, *wrup;
	idtype_t idtype;
	id_t id;
	int ret;

	/*
	 * Translate the special pid values into the (idtype, pid)
	 * pair for kern_wait6.  The WAIT_MYPGRP case is handled by
	 * kern_wait6() on its own.
	 */
	if (pid == WAIT_ANY) {
		idtype = P_ALL;
		id = 0;
	} else if (pid < 0) {
		idtype = P_PGID;
		id = (id_t)-pid;
	} else {
		idtype = P_PID;
		id = (id_t)pid;
	}

	if (rusage != NULL)
		wrup = &wru;
	else
		wrup = NULL;

	/*
	 * For backward compatibility we implicitly add flags WEXITED
	 * and WTRAPPED here.
	 */
	options |= WEXITED | WTRAPPED;
	ret = kern_wait6(td, idtype, id, status, options, wrup, NULL);
	if (rusage != NULL)
		*rusage = wru.wru_self;
	return (ret);
}