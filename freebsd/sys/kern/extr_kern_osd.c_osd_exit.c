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
struct osd {size_t osd_nslots; int /*<<< orphan*/ * osd_slots; } ;
struct TYPE_2__ {int /*<<< orphan*/  osd_object_lock; int /*<<< orphan*/ ** osd_destructors; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  OSD_DEBUG (char*,size_t,...) ; 
 size_t OSD_FIRST ; 
 size_t OSD_LAST ; 
 int /*<<< orphan*/  do_osd_del (size_t,struct osd*,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* osdm ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 

void
osd_exit(u_int type, struct osd *osd)
{
	struct rm_priotracker tracker;
	u_int i;

	KASSERT(type >= OSD_FIRST && type <= OSD_LAST, ("Invalid type."));

	if (osd->osd_nslots == 0) {
		KASSERT(osd->osd_slots == NULL, ("Non-null osd_slots."));
		/* No OSD attached, just leave. */
		return;
	}

	rm_rlock(&osdm[type].osd_object_lock, &tracker);
	for (i = 1; i <= osd->osd_nslots; i++) {
		if (osdm[type].osd_destructors[i - 1] != NULL)
			do_osd_del(type, osd, i, 0);
		else
			OSD_DEBUG("Unused slot (type=%u, slot=%u).", type, i);
	}
	rm_runlock(&osdm[type].osd_object_lock, &tracker);
	OSD_DEBUG("Object exit (type=%u).", type);
}