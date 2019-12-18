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
struct rlimit {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int KERN_PROC ; 
 int KERN_PROC_RLIMIT ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int sysctl (int*,int,struct rlimit*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
getrlimit_proc(pid_t pid, int resource, struct rlimit *rlp)
{
    int error;
    int name[5];
    size_t len;

    name[0] = CTL_KERN;
    name[1] = KERN_PROC;
    name[2] = KERN_PROC_RLIMIT;
    name[3] = pid;
    name[4] = resource;
    len = sizeof(*rlp);
    error = sysctl(name, 5, rlp, &len, NULL, 0);
    if (error == -1)
	err(EXIT_FAILURE, "sysctl: kern.proc.rlimit: %d", pid);
    if (len != sizeof(*rlp))
	errx(EXIT_FAILURE, "sysctl() returns wrong size");
}