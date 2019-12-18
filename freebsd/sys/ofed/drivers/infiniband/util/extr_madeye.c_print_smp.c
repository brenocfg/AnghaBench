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
struct ib_smp {int /*<<< orphan*/ * return_path; int /*<<< orphan*/ * initial_path; int /*<<< orphan*/ * data; scalar_t__ dr_dlid; scalar_t__ dr_slid; int /*<<< orphan*/  mkey; int /*<<< orphan*/  attr_mod; scalar_t__ attr_id; int /*<<< orphan*/  tid; int /*<<< orphan*/  hop_cnt; int /*<<< orphan*/  hop_ptr; scalar_t__ status; int /*<<< orphan*/  method; int /*<<< orphan*/  mgmt_class; int /*<<< orphan*/  class_version; int /*<<< orphan*/  base_version; } ;

/* Variables and functions */
 int IB_SMP_DATA_SIZE ; 
 int IB_SMP_MAX_PATH_HOPS ; 
 int /*<<< orphan*/  be16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ data ; 
 int /*<<< orphan*/  get_class_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_method_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_smp_attr (scalar_t__) ; 
 int /*<<< orphan*/  print_status_details (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void print_smp(struct ib_smp *smp)
{
	int i;

	printk("MAD version....0x%01x\n", smp->base_version);
	printk("Class..........0x%01x (%s)\n", smp->mgmt_class,
	       get_class_name(smp->mgmt_class));
	printk("Class version..0x%01x\n", smp->class_version);
	printk("Method.........0x%01x (%s)\n", smp->method,
	       get_method_name(smp->mgmt_class, smp->method));
	printk("Status.........0x%02x\n", be16_to_cpu(smp->status));
	if (smp->status)
		print_status_details(be16_to_cpu(smp->status));
	printk("Hop pointer....0x%01x\n", smp->hop_ptr);
	printk("Hop counter....0x%01x\n", smp->hop_cnt);
	printk("Trans ID.......0x%llx\n", 
		(unsigned long long)be64_to_cpu(smp->tid));
	printk("Attr ID........0x%02x (%s)\n", be16_to_cpu(smp->attr_id),
		get_smp_attr(smp->attr_id));
	printk("Attr modifier..0x%04x\n", be32_to_cpu(smp->attr_mod));

	printk("Mkey...........0x%llx\n",
		(unsigned long long)be64_to_cpu(smp->mkey));
	printk("DR SLID........0x%02x\n", be16_to_cpu(smp->dr_slid));
	printk("DR DLID........0x%02x", be16_to_cpu(smp->dr_dlid));

	if (data) {
		for (i = 0; i < IB_SMP_DATA_SIZE; i++) {
			if (i % 16 == 0)
				printk("\nSMP Data.......");
			printk("%01x ", smp->data[i]);
		}
		for (i = 0; i < IB_SMP_MAX_PATH_HOPS; i++) {
			if (i % 16 == 0)
				printk("\nInitial path...");
			printk("%01x ", smp->initial_path[i]);
		}
		for (i = 0; i < IB_SMP_MAX_PATH_HOPS; i++) {
			if (i % 16 == 0)
				printk("\nReturn path....");
			printk("%01x ", smp->return_path[i]);
		}
	}
	printk("\n");
}