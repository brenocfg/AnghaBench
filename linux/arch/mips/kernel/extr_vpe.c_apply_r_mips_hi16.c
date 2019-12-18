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
typedef  int /*<<< orphan*/  uint32_t ;
struct module {int dummy; } ;
struct mips_hi16 {struct mips_hi16* next; int /*<<< orphan*/  value; int /*<<< orphan*/ * addr; } ;
typedef  int /*<<< orphan*/  Elf32_Addr ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mips_hi16* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct mips_hi16* mips_hi16_list ; 

__attribute__((used)) static int apply_r_mips_hi16(struct module *me, uint32_t *location,
			     Elf32_Addr v)
{
	struct mips_hi16 *n;

	/*
	 * We cannot relocate this one now because we don't know the value of
	 * the carry we need to add.  Save the information, and let LO16 do the
	 * actual relocation.
	 */
	n = kmalloc(sizeof(*n), GFP_KERNEL);
	if (!n)
		return -ENOMEM;

	n->addr = location;
	n->value = v;
	n->next = mips_hi16_list;
	mips_hi16_list = n;

	return 0;
}