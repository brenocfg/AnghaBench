#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct netmap_mem_d {TYPE_1__* next; struct netmap_mem_d* prev; } ;
struct TYPE_2__ {struct netmap_mem_d* prev; } ;

/* Variables and functions */
 struct netmap_mem_d* netmap_last_mem_d ; 

__attribute__((used)) static void
nm_mem_release_id(struct netmap_mem_d *nmd)
{
	nmd->prev->next = nmd->next;
	nmd->next->prev = nmd->prev;

	if (netmap_last_mem_d == nmd)
		netmap_last_mem_d = nmd->prev;

	nmd->prev = nmd->next = NULL;
}