#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* current_size; } ;
struct TYPE_5__ {int gart_size; } ;
struct TYPE_4__ {int size; } ;

/* Variables and functions */
 int MB (int) ; 
 TYPE_3__* agp_bridge ; 
 TYPE_2__ parisc_agp_info ; 
 TYPE_1__* parisc_agp_sizes ; 

__attribute__((used)) static int
parisc_agp_fetch_size(void)
{
	int size;

	size = parisc_agp_info.gart_size / MB(1);
	parisc_agp_sizes[0].size = size;
	agp_bridge->current_size = (void *) &parisc_agp_sizes[0];

	return size;
}