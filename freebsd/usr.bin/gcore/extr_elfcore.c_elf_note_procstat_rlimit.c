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
typedef  int /*<<< orphan*/  structsize ;
struct rlimit {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PROC ; 
 int KERN_PROC_RLIMIT ; 
 int RLIM_NLIMITS ; 
 int /*<<< orphan*/  bcopy (int*,void*,int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*,int) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int sysctl (int*,int,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
elf_note_procstat_rlimit(void *arg, size_t *sizep)
{
	pid_t pid;
	size_t len;
	int i, name[5], structsize;
	void *buf, *p;

	pid = *(pid_t *)arg;
	structsize = sizeof(struct rlimit) * RLIM_NLIMITS;
	buf = calloc(1, sizeof(structsize) + structsize);
	if (buf == NULL)
		errx(1, "out of memory");
	bcopy(&structsize, buf, sizeof(structsize));
	p = (char *)buf + sizeof(structsize);
	name[0] = CTL_KERN;
	name[1] = KERN_PROC;
	name[2] = KERN_PROC_RLIMIT;
	name[3] = pid;
	len = sizeof(struct rlimit);
	for (i = 0; i < RLIM_NLIMITS; i++) {
		name[4] = i;
		if (sysctl(name, 5, p, &len, NULL, 0) == -1)
			err(1, "kern.proc.rlimit.%u", pid);
		if (len != sizeof(struct rlimit))
			errx(1, "kern.proc.rlimit.%u: short read", pid);
		p += len;
	}

	*sizep = sizeof(structsize) + structsize;
	return (buf);
}