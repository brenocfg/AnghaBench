#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proc_dir_entry {int dummy; } ;
struct TYPE_3__ {unsigned int req_cpu; int func_id; scalar_t__ value; } ;
typedef  TYPE_1__ pal_func_cpu_u_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int NR_PALINFO_ENTRIES ; 
 int /*<<< orphan*/  palinfo_dir ; 
 TYPE_2__* palinfo_entries ; 
 int /*<<< orphan*/  proc_create_single_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc_dir_entry*,int /*<<< orphan*/ ,void*) ; 
 struct proc_dir_entry* proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_palinfo_show ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 

__attribute__((used)) static int palinfo_add_proc(unsigned int cpu)
{
	pal_func_cpu_u_t f;
	struct proc_dir_entry *cpu_dir;
	int j;
	char cpustr[3+4+1];	/* cpu numbers are up to 4095 on itanic */
	sprintf(cpustr, "cpu%d", cpu);

	cpu_dir = proc_mkdir(cpustr, palinfo_dir);
	if (!cpu_dir)
		return -EINVAL;

	f.req_cpu = cpu;

	for (j=0; j < NR_PALINFO_ENTRIES; j++) {
		f.func_id = j;
		proc_create_single_data(palinfo_entries[j].name, 0, cpu_dir,
				proc_palinfo_show, (void *)f.value);
	}
	return 0;
}