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
struct seminfo {int semmni; int semmns; int semmnu; int semmsl; int semopm; int semume; int semusz; int semvmx; int semaem; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
print_ksemtotal(struct seminfo local_seminfo)
{

	printf("seminfo:\n");
	printf("\tsemmni: %12d\t(# of semaphore identifiers)\n",
	    local_seminfo.semmni);
	printf("\tsemmns: %12d\t(# of semaphores in system)\n",
	    local_seminfo.semmns);
	printf("\tsemmnu: %12d\t(# of undo structures in system)\n",
	    local_seminfo.semmnu);
	printf("\tsemmsl: %12d\t(max # of semaphores per id)\n",
	    local_seminfo.semmsl);
	printf("\tsemopm: %12d\t(max # of operations per semop call)\n",
	    local_seminfo.semopm);
	printf("\tsemume: %12d\t(max # of undo entries per process)\n",
	    local_seminfo.semume);
	printf("\tsemusz: %12d\t(size in bytes of undo structure)\n",
	    local_seminfo.semusz);
	printf("\tsemvmx: %12d\t(semaphore maximum value)\n",
	    local_seminfo.semvmx);
	printf("\tsemaem: %12d\t(adjust on exit max value)\n\n",
	    local_seminfo.semaem);
}