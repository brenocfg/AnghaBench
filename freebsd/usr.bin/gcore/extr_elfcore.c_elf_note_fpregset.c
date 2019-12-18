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
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  fpregset_t ;
typedef  void elfcore_fpregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  PT_GETFPREGS ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  elf_convert_fpregset (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
elf_note_fpregset(void *arg, size_t *sizep)
{
	lwpid_t tid;
	elfcore_fpregset_t *fpregset;
	fpregset_t fpreg;

	tid = *(lwpid_t *)arg;
	fpregset = calloc(1, sizeof(*fpregset));
	if (fpregset == NULL)
		errx(1, "out of memory");
	ptrace(PT_GETFPREGS, tid, (void *)&fpreg, 0);
	elf_convert_fpregset(fpregset, &fpreg);

	*sizep = sizeof(*fpregset);
	return (fpregset);
}