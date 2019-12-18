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
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  idtype_t ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 size_t INTERPOS_wait6 ; 
 scalar_t__* __libc_interposing ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,struct __wrusage*,int /*<<< orphan*/ *) ; 

int
__waitid(idtype_t idtype, id_t id, siginfo_t *info, int flags)
{
	int status;
	pid_t ret;

	ret = ((pid_t (*)(idtype_t, id_t, int *, int, struct __wrusage *,
	    siginfo_t *))__libc_interposing[INTERPOS_wait6])(idtype, id,
	    &status, flags, NULL, info);

	/*
	 * According to SUSv4, waitid() shall not return a PID when a
	 * process is found, but only 0.  If a process was actually
	 * found, siginfo_t fields si_signo and si_pid will be
	 * non-zero.  In case WNOHANG was set in the flags and no
	 * process was found those fields are set to zero using
	 * memset() below.
	 */
	if (ret == 0 && info != NULL)
		memset(info, 0, sizeof(*info));
	else if (ret > 0)
		ret = 0;
	return (ret);
}