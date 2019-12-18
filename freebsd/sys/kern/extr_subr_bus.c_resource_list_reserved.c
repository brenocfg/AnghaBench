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
struct resource_list_entry {int flags; } ;
struct resource_list {int dummy; } ;

/* Variables and functions */
 int RLE_RESERVED ; 
 struct resource_list_entry* resource_list_find (struct resource_list*,int,int) ; 

int
resource_list_reserved(struct resource_list *rl, int type, int rid)
{
	struct resource_list_entry *rle;

	rle = resource_list_find(rl, type, rid);
	if (rle != NULL && rle->flags & RLE_RESERVED)
		return (1);
	return (0);
}