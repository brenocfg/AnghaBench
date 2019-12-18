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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct agp_gatt {int ag_entries; scalar_t__ ag_virtual; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_AGP ; 
 int /*<<< orphan*/  free (struct agp_gatt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int) ; 

void
agp_free_gatt(struct agp_gatt *gatt)
{
	kmem_free((vm_offset_t)gatt->ag_virtual, gatt->ag_entries *
	    sizeof(u_int32_t));
	free(gatt, M_AGP);
}