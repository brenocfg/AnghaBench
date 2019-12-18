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
typedef  size_t u_int ;
struct rm_priotracker {int dummy; } ;
struct osd {size_t osd_nslots; void** osd_slots; } ;
struct TYPE_2__ {int /*<<< orphan*/  osd_object_lock; int /*<<< orphan*/ ** osd_destructors; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  OSD_DEBUG (char*,size_t,size_t,...) ; 
 size_t OSD_FIRST ; 
 size_t OSD_LAST ; 
 TYPE_1__* osdm ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 

void *
osd_get(u_int type, struct osd *osd, u_int slot)
{
	struct rm_priotracker tracker;
	void *value;

	KASSERT(type >= OSD_FIRST && type <= OSD_LAST, ("Invalid type."));
	KASSERT(slot > 0, ("Invalid slot."));
	KASSERT(osdm[type].osd_destructors[slot - 1] != NULL, ("Unused slot."));

	rm_rlock(&osdm[type].osd_object_lock, &tracker);
	if (slot > osd->osd_nslots) {
		value = NULL;
		OSD_DEBUG("Slot doesn't exist (type=%u, slot=%u).", type, slot);
	} else {
		value = osd->osd_slots[slot - 1];
		OSD_DEBUG("Returning slot value (type=%u, slot=%u, value=%p).",
		    type, slot, value);
	}
	rm_runlock(&osdm[type].osd_object_lock, &tracker);
	return (value);
}