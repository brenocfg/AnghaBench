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
struct pfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PFS_RD ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linsysfs_cpuxonline ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mp_maxcpus ; 
 int mp_ncpus ; 
 struct pfs_node* pfs_create_dir (struct pfs_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfs_create_file (struct pfs_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void
linsysfs_listcpus(struct pfs_node *dir)
{
	struct pfs_node *cpu;
	char *name;
	int i, count, len;

	len = 1;
	count = mp_maxcpus;
	while (count > 10) {
		count /= 10;
		len++;
	}
	len += sizeof("cpu");
	name = malloc(len, M_TEMP, M_WAITOK);

	for (i = 0; i < mp_ncpus; ++i) {
		/* /sys/devices/system/cpu/cpuX */
		sprintf(name, "cpu%d", i);
		cpu = pfs_create_dir(dir, name, NULL, NULL, NULL, 0);

		pfs_create_file(cpu, "online", &linsysfs_cpuxonline,
		    NULL, NULL, NULL, PFS_RD);
	}
	free(name, M_TEMP);
}