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
struct ib_mad_hdr {unsigned long long base_version; scalar_t__ mgmt_class; unsigned long long class_version; int /*<<< orphan*/  attr_mod; scalar_t__ attr_id; int /*<<< orphan*/  tid; scalar_t__ class_specific; scalar_t__ status; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 scalar_t__ IB_MGMT_CLASS_SUBN_ADM ; 
 unsigned long long be16_to_cpu (scalar_t__) ; 
 unsigned long long be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_class_name (scalar_t__) ; 
 int /*<<< orphan*/  get_method_name (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_sa_attr (unsigned long long) ; 
 int /*<<< orphan*/  print_status_details (unsigned long long) ; 
 int /*<<< orphan*/  printk (char*,unsigned long long,...) ; 

__attribute__((used)) static void print_mad_hdr(struct ib_mad_hdr *mad_hdr)
{
	printk("MAD version....0x%01x\n", mad_hdr->base_version);
	printk("Class..........0x%01x (%s)\n", mad_hdr->mgmt_class,
	       get_class_name(mad_hdr->mgmt_class));
	printk("Class version..0x%01x\n", mad_hdr->class_version);
	printk("Method.........0x%01x (%s)\n", mad_hdr->method,
	       get_method_name(mad_hdr->mgmt_class, mad_hdr->method));
	printk("Status.........0x%02x\n", be16_to_cpu(mad_hdr->status));
	if (mad_hdr->status)
		print_status_details(be16_to_cpu(mad_hdr->status));
	printk("Class specific.0x%02x\n", be16_to_cpu(mad_hdr->class_specific));
	printk("Trans ID.......0x%llx\n", 
		(unsigned long long)be64_to_cpu(mad_hdr->tid));
	if (mad_hdr->mgmt_class == IB_MGMT_CLASS_SUBN_ADM)
		printk("Attr ID........0x%02x (%s)\n",
		       be16_to_cpu(mad_hdr->attr_id),
		       get_sa_attr(be16_to_cpu(mad_hdr->attr_id)));
	else
		printk("Attr ID........0x%02x\n",
		       be16_to_cpu(mad_hdr->attr_id));
	printk("Attr modifier..0x%04x\n", be32_to_cpu(mad_hdr->attr_mod));
}