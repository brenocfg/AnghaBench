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
typedef  scalar_t__ vm_offset_t ;
struct mem_region {scalar_t__ mr_start; scalar_t__ mr_size; } ;

/* Variables and functions */
 scalar_t__ uqmax (scalar_t__,scalar_t__) ; 
 scalar_t__ uqmin (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
memr_merge(struct mem_region *from, struct mem_region *to)
{
	vm_offset_t end;
	end = uqmax(to->mr_start + to->mr_size, from->mr_start + from->mr_size);
	to->mr_start = uqmin(from->mr_start, to->mr_start);
	to->mr_size = end - to->mr_start;
}