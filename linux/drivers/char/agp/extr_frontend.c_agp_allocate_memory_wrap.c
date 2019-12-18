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
typedef  int /*<<< orphan*/  u32 ;
struct agp_memory {int dummy; } ;

/* Variables and functions */
 struct agp_memory* agp_allocate_memory (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_bridge ; 
 int /*<<< orphan*/  agp_insert_into_pool (struct agp_memory*) ; 

struct agp_memory *agp_allocate_memory_wrap(size_t pg_count, u32 type)
{
	struct agp_memory *memory;

	memory = agp_allocate_memory(agp_bridge, pg_count, type);
	if (memory == NULL)
		return NULL;

	agp_insert_into_pool(memory);
	return memory;
}