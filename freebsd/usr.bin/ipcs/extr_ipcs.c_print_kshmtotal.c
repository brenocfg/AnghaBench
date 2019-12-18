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
struct shminfo {int /*<<< orphan*/  shmall; int /*<<< orphan*/  shmseg; int /*<<< orphan*/  shmmni; int /*<<< orphan*/  shmmin; int /*<<< orphan*/  shmmax; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
print_kshmtotal(struct shminfo local_shminfo)
{

	printf("shminfo:\n");
	printf("\tshmmax: %12lu\t(max shared memory segment size)\n",
	    local_shminfo.shmmax);
	printf("\tshmmin: %12lu\t(min shared memory segment size)\n",
	    local_shminfo.shmmin);
	printf("\tshmmni: %12lu\t(max number of shared memory identifiers)\n",
	    local_shminfo.shmmni);
	printf("\tshmseg: %12lu\t(max shared memory segments per process)\n",
	    local_shminfo.shmseg);
	printf("\tshmall: %12lu\t(max amount of shared memory in pages)\n\n",
	    local_shminfo.shmall);
}