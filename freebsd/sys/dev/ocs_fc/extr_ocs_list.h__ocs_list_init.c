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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  offset; struct TYPE_4__* prev; struct TYPE_4__* next; } ;
typedef  TYPE_1__ ocs_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_list_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_list_set_list_magic ; 

__attribute__((used)) static inline void
_ocs_list_init(ocs_list_t *list, uint32_t offset)
{
	ocs_list_assert(list);
	ocs_list_set_list_magic;

	list->next = list;
	list->prev = list;
	list->offset = offset;
}