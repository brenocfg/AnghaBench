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
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_OSD ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OSD_DEBUG (char*,int) ; 
 void** malloc (int,int /*<<< orphan*/ ,int) ; 

void **
osd_reserve(u_int slot)
{

	KASSERT(slot > 0, ("Invalid slot."));

	OSD_DEBUG("Reserving slot array (slot=%u).", slot);
	return (malloc(sizeof(void *) * slot, M_OSD, M_WAITOK | M_ZERO));
}