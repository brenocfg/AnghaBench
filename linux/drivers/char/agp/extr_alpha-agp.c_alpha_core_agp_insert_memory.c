#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct agp_memory {int type; int page_count; } ;
typedef  int off_t ;
struct TYPE_7__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ alpha_agp_info ;
struct TYPE_9__ {int num_entries; } ;
struct TYPE_8__ {void* current_size; TYPE_2__* dev_private_data; } ;
struct TYPE_6__ {int (* bind ) (TYPE_2__*,int,struct agp_memory*) ;} ;

/* Variables and functions */
 int AGP_USER_TYPES ; 
 TYPE_5__* A_SIZE_FIX (void*) ; 
 int EINVAL ; 
 TYPE_4__* agp_bridge ; 
 int /*<<< orphan*/  alpha_core_agp_tlbflush (struct agp_memory*) ; 
 int /*<<< orphan*/  mb () ; 
 int stub1 (TYPE_2__*,int,struct agp_memory*) ; 

__attribute__((used)) static int alpha_core_agp_insert_memory(struct agp_memory *mem, off_t pg_start,
					int type)
{
	alpha_agp_info *agp = agp_bridge->dev_private_data;
	int num_entries, status;
	void *temp;

	if (type >= AGP_USER_TYPES || mem->type >= AGP_USER_TYPES)
		return -EINVAL;

	temp = agp_bridge->current_size;
	num_entries = A_SIZE_FIX(temp)->num_entries;
	if ((pg_start + mem->page_count) > num_entries)
		return -EINVAL;

	status = agp->ops->bind(agp, pg_start, mem);
	mb();
	alpha_core_agp_tlbflush(mem);

	return status;
}