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
struct TYPE_3__ {unsigned int vm_hashsize; struct vmem_hashlist* vm_hashlist; } ;
typedef  TYPE_1__ vmem_t ;
typedef  int /*<<< orphan*/  vmem_addr_t ;
struct vmem_hashlist {int dummy; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 unsigned int hash32_buf (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct vmem_hashlist *
bt_hashhead(vmem_t *vm, vmem_addr_t addr)
{
	struct vmem_hashlist *list;
	unsigned int hash;

	hash = hash32_buf(&addr, sizeof(addr), 0);
	list = &vm->vm_hashlist[hash % vm->vm_hashsize];

	return list;
}