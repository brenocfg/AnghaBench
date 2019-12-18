#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct procabi {int dummy; } ;
typedef  int /*<<< orphan*/  progt ;
typedef  int pid_t ;
struct TYPE_3__ {struct procabi* abi; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PROC ; 
 int KERN_PROC_SV_NAME ; 
 TYPE_1__* abis ; 
 int /*<<< orphan*/  err (int,char*) ; 
 unsigned int nitems (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*,long) ; 

__attribute__((used)) static struct procabi *
find_abi(pid_t pid)
{
	size_t len;
	unsigned int i;
	int error;
	int mib[4];
	char progt[32];

	len = sizeof(progt);
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROC;
	mib[2] = KERN_PROC_SV_NAME;
	mib[3] = pid;
	error = sysctl(mib, 4, progt, &len, NULL, 0);
	if (error != 0)
		err(2, "can not get sysvec name");

	for (i = 0; i < nitems(abis); i++) {
		if (strcmp(abis[i].name, progt) == 0)
			return (abis[i].abi);
	}
	warnx("ABI %s for pid %ld is not supported", progt, (long)pid);
	return (NULL);
}