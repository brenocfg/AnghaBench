#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int num_entries; } ;
struct TYPE_13__ {int num_entries; } ;
struct TYPE_12__ {int num_entries; } ;
struct TYPE_11__ {int num_entries; } ;
struct TYPE_10__ {int num_entries; } ;
struct TYPE_9__ {TYPE_1__* driver; void* current_size; } ;
struct TYPE_8__ {int size_type; } ;

/* Variables and functions */
 TYPE_7__* A_SIZE_16 (void*) ; 
 TYPE_6__* A_SIZE_32 (void*) ; 
 TYPE_5__* A_SIZE_8 (void*) ; 
 TYPE_4__* A_SIZE_FIX (void*) ; 
 TYPE_3__* A_SIZE_LVL2 (void*) ; 
#define  FIXED_APER_SIZE 132 
#define  LVL2_APER_SIZE 131 
 int PAGE_SHIFT ; 
#define  U16_APER_SIZE 130 
#define  U32_APER_SIZE 129 
#define  U8_APER_SIZE 128 
 TYPE_2__* agp_bridge ; 
 int agp_memory_reserved ; 

int agp_num_entries(void)
{
	int num_entries;
	void *temp;

	temp = agp_bridge->current_size;

	switch (agp_bridge->driver->size_type) {
	case U8_APER_SIZE:
		num_entries = A_SIZE_8(temp)->num_entries;
		break;
	case U16_APER_SIZE:
		num_entries = A_SIZE_16(temp)->num_entries;
		break;
	case U32_APER_SIZE:
		num_entries = A_SIZE_32(temp)->num_entries;
		break;
	case LVL2_APER_SIZE:
		num_entries = A_SIZE_LVL2(temp)->num_entries;
		break;
	case FIXED_APER_SIZE:
		num_entries = A_SIZE_FIX(temp)->num_entries;
		break;
	default:
		num_entries = 0;
		break;
	}

	num_entries -= agp_memory_reserved>>PAGE_SHIFT;
	if (num_entries<0)
		num_entries = 0;
	return num_entries;
}