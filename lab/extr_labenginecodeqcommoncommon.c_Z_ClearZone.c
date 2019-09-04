#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tag; scalar_t__ size; scalar_t__ id; TYPE_3__* prev; TYPE_3__* next; } ;
struct TYPE_6__ {int size; TYPE_1__ blocklist; scalar_t__ used; TYPE_3__* rover; } ;
typedef  TYPE_2__ memzone_t ;
struct TYPE_7__ {int size; int /*<<< orphan*/  id; scalar_t__ tag; TYPE_1__* next; TYPE_1__* prev; } ;
typedef  TYPE_3__ memblock_t ;
typedef  int /*<<< orphan*/  byte ;

/* Variables and functions */
 int /*<<< orphan*/  ZONEID ; 

__attribute__((used)) static void Z_ClearZone( memzone_t *zone, int size ) {
	memblock_t	*block;
	
	// set the entire zone to one free block

	zone->blocklist.next = zone->blocklist.prev = block =
		(memblock_t *)( (byte *)zone + sizeof(memzone_t) );
	zone->blocklist.tag = 1;	// in use block
	zone->blocklist.id = 0;
	zone->blocklist.size = 0;
	zone->rover = block;
	zone->size = size;
	zone->used = 0;
	
	block->prev = block->next = &zone->blocklist;
	block->tag = 0;			// free block
	block->id = ZONEID;
	block->size = size - sizeof(memzone_t);
}