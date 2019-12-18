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
struct trussinfo {struct threadinfo* curthread; } ;
struct threadinfo {int dummy; } ;
struct ptrace_lwpinfo {int pl_flags; } ;
struct procinfo {int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  pl ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int PL_FLAG_SCE ; 
 int /*<<< orphan*/  PT_GETLWPLIST ; 
 int /*<<< orphan*/  PT_GETNUMLWPS ; 
 int /*<<< orphan*/  PT_LWPINFO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  enter_syscall (struct trussinfo*,struct threadinfo*,struct ptrace_lwpinfo*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 struct threadinfo* new_thread (struct procinfo*,int /*<<< orphan*/ ) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
add_threads(struct trussinfo *info, struct procinfo *p)
{
	struct ptrace_lwpinfo pl;
	struct threadinfo *t;
	lwpid_t *lwps;
	int i, nlwps;

	nlwps = ptrace(PT_GETNUMLWPS, p->pid, NULL, 0);
	if (nlwps == -1)
		err(1, "Unable to fetch number of LWPs");
	assert(nlwps > 0);
	lwps = calloc(nlwps, sizeof(*lwps));
	nlwps = ptrace(PT_GETLWPLIST, p->pid, (caddr_t)lwps, nlwps);
	if (nlwps == -1)
		err(1, "Unable to fetch LWP list");
	for (i = 0; i < nlwps; i++) {
		t = new_thread(p, lwps[i]);
		if (ptrace(PT_LWPINFO, lwps[i], (caddr_t)&pl, sizeof(pl)) == -1)
			err(1, "ptrace(PT_LWPINFO)");
		if (pl.pl_flags & PL_FLAG_SCE) {
			info->curthread = t;
			enter_syscall(info, t, &pl);
		}
	}
	free(lwps);
}