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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct ldttss_desc {int base0; int base1; int limit0; int limit1; scalar_t__ base3; scalar_t__ base2; } ;
struct desc_struct {int dummy; } ;
struct desc_ptr {scalar_t__ size; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_alert (char*,char const*,...) ; 
 scalar_t__ probe_kernel_read (struct ldttss_desc*,void*,int) ; 

__attribute__((used)) static void show_ldttss(const struct desc_ptr *gdt, const char *name, u16 index)
{
	u32 offset = (index >> 3) * sizeof(struct desc_struct);
	unsigned long addr;
	struct ldttss_desc desc;

	if (index == 0) {
		pr_alert("%s: NULL\n", name);
		return;
	}

	if (offset + sizeof(struct ldttss_desc) >= gdt->size) {
		pr_alert("%s: 0x%hx -- out of bounds\n", name, index);
		return;
	}

	if (probe_kernel_read(&desc, (void *)(gdt->address + offset),
			      sizeof(struct ldttss_desc))) {
		pr_alert("%s: 0x%hx -- GDT entry is not readable\n",
			 name, index);
		return;
	}

	addr = desc.base0 | (desc.base1 << 16) | ((unsigned long)desc.base2 << 24);
#ifdef CONFIG_X86_64
	addr |= ((u64)desc.base3 << 32);
#endif
	pr_alert("%s: 0x%hx -- base=0x%lx limit=0x%x\n",
		 name, index, addr, (desc.limit0 | (desc.limit1 << 16)));
}