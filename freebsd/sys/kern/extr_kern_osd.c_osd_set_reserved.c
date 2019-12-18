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
struct TYPE_2__ {int /*<<< orphan*/  osd_object_lock; int /*<<< orphan*/  osd_list_lock; int /*<<< orphan*/  osd_list; int /*<<< orphan*/ ** osd_destructors; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct osd*,int /*<<< orphan*/ ) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_OSD ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OSD_DEBUG (char*,size_t,...) ; 
 size_t OSD_FIRST ; 
 size_t OSD_LAST ; 
 int /*<<< orphan*/  free (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_free_reserved (void**) ; 
 int /*<<< orphan*/  osd_next ; 
 TYPE_1__* osdm ; 
 void** realloc (void**,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 

int
osd_set_reserved(u_int type, struct osd *osd, u_int slot, void **rsv,
    void *value)
{
	struct rm_priotracker tracker;

	KASSERT(type >= OSD_FIRST && type <= OSD_LAST, ("Invalid type."));
	KASSERT(slot > 0, ("Invalid slot."));
	KASSERT(osdm[type].osd_destructors[slot - 1] != NULL, ("Unused slot."));

	rm_rlock(&osdm[type].osd_object_lock, &tracker);
	if (slot > osd->osd_nslots) {
		void **newptr;

		if (value == NULL) {
			OSD_DEBUG(
			    "Not allocating null slot (type=%u, slot=%u).",
			    type, slot);
			rm_runlock(&osdm[type].osd_object_lock, &tracker);
			if (rsv)
				osd_free_reserved(rsv);
			return (0);
		}

		/*
		 * Too few slots allocated here, so we need to extend or create
		 * the array.
		 */
		if (rsv) {
			/*
			 * Use the reserve passed in (assumed to be
			 * the right size).
			 */
			newptr = rsv;
			if (osd->osd_nslots != 0) {
				memcpy(newptr, osd->osd_slots,
				    sizeof(void *) * osd->osd_nslots);
				free(osd->osd_slots, M_OSD);
			}
		} else {
			newptr = realloc(osd->osd_slots, sizeof(void *) * slot,
			    M_OSD, M_NOWAIT | M_ZERO);
			if (newptr == NULL) {
				rm_runlock(&osdm[type].osd_object_lock,
				    &tracker);
				return (ENOMEM);
			}
		}
		if (osd->osd_nslots == 0) {
			/*
			 * First OSD for this object, so we need to put it
			 * onto the list.
			 */
			mtx_lock(&osdm[type].osd_list_lock);
			LIST_INSERT_HEAD(&osdm[type].osd_list, osd, osd_next);
			mtx_unlock(&osdm[type].osd_list_lock);
			OSD_DEBUG("Setting first slot (type=%u).", type);
		} else
			OSD_DEBUG("Growing slots array (type=%u).", type);
		osd->osd_slots = newptr;
		osd->osd_nslots = slot;
	} else if (rsv)
		osd_free_reserved(rsv);
	OSD_DEBUG("Setting slot value (type=%u, slot=%u, value=%p).", type,
	    slot, value);
	osd->osd_slots[slot - 1] = value;
	rm_runlock(&osdm[type].osd_object_lock, &tracker);
	return (0);
}