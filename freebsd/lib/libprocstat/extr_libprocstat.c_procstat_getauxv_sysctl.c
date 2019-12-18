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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  Elf_Auxinfo ;

/* Variables and functions */
 int CTL_KERN ; 
 scalar_t__ EPERM ; 
 scalar_t__ ESRCH ; 
 int KERN_PROC ; 
 int KERN_PROC_AUXV ; 
 int PROC_AUXV_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ is_elf32_sysctl (int) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  nitems (int*) ; 
 int /*<<< orphan*/ * procstat_getauxv32_sysctl (int,unsigned int*) ; 
 int sysctl (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int,...) ; 

__attribute__((used)) static Elf_Auxinfo *
procstat_getauxv_sysctl(pid_t pid, unsigned int *cntp)
{
	Elf_Auxinfo *auxv;
	int name[4];
	size_t len;

#if __ELF_WORD_SIZE == 64
	if (is_elf32_sysctl(pid))
		return (procstat_getauxv32_sysctl(pid, cntp));
#endif
	name[0] = CTL_KERN;
	name[1] = KERN_PROC;
	name[2] = KERN_PROC_AUXV;
	name[3] = pid;
	len = PROC_AUXV_MAX * sizeof(Elf_Auxinfo);
	auxv = malloc(len);
	if (auxv == NULL) {
		warn("malloc(%zu)", len);
		return (NULL);
	}
	if (sysctl(name, nitems(name), auxv, &len, NULL, 0) == -1) {
		if (errno != ESRCH && errno != EPERM)
			warn("sysctl: kern.proc.auxv: %d: %d", pid, errno);
		free(auxv);
		return (NULL);
	}
	*cntp = len / sizeof(Elf_Auxinfo);
	return (auxv);
}