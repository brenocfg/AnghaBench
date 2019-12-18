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
struct agp_memory {struct agp_memory* next; } ;
struct agp_controller {struct agp_memory* pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  agp_free_memory_wrap (struct agp_memory*) ; 

__attribute__((used)) static void agp_remove_all_memory(struct agp_controller *controller)
{
	struct agp_memory *memory;
	struct agp_memory *temp;

	memory = controller->pool;

	while (memory) {
		temp = memory;
		memory = memory->next;
		agp_free_memory_wrap(temp);
	}
}