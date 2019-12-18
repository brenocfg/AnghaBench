#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_object_t ;
struct TYPE_4__ {scalar_t__ type; } ;

/* Variables and functions */
 int MADV_FREE ; 
 scalar_t__ OBJT_SWAP ; 
 int /*<<< orphan*/  swap_pager_freespace (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_object_madvise_freespace(vm_object_t object, int advice, vm_pindex_t pindex,
    vm_size_t size)
{

	if (advice == MADV_FREE && object->type == OBJT_SWAP)
		swap_pager_freespace(object, pindex, size);
}