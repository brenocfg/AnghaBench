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
struct ptrace_lwpinfo {int dummy; } ;
typedef  int /*<<< orphan*/  lwpinfo ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  elfcore_lwpinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  PT_LWPINFO ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  elf_convert_lwpinfo (int /*<<< orphan*/ *,struct ptrace_lwpinfo*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void *
elf_note_ptlwpinfo(void *arg, size_t *sizep)
{
	lwpid_t tid;
	elfcore_lwpinfo_t *elf_info;
	struct ptrace_lwpinfo lwpinfo;
	void *p;

	tid = *(lwpid_t *)arg;
	p = calloc(1, sizeof(int) + sizeof(elfcore_lwpinfo_t));
	if (p == NULL)
		errx(1, "out of memory");
	*(int *)p = sizeof(elfcore_lwpinfo_t);
	elf_info = (void *)((int *)p + 1);
	ptrace(PT_LWPINFO, tid, (void *)&lwpinfo, sizeof(lwpinfo));
	elf_convert_lwpinfo(elf_info, &lwpinfo);

	*sizep = sizeof(int) + sizeof(struct ptrace_lwpinfo);
	return (p);
}