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
typedef  size_t u_int ;
struct sysentvec {char const** sv_syscallnames; size_t sv_size; } ;
struct proc {struct sysentvec* p_sysent; } ;

/* Variables and functions */

const char *
syscallname(struct proc *p, u_int code)
{
	static const char unknown[] = "unknown";
	struct sysentvec *sv;

	sv = p->p_sysent;
	if (sv->sv_syscallnames == NULL || code >= sv->sv_size)
		return (unknown);
	return (sv->sv_syscallnames[code]);
}