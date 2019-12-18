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
struct osd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  osd_object_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_osd_del (size_t,struct osd*,size_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* osdm ; 
 int /*<<< orphan*/  rm_rlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 
 int /*<<< orphan*/  rm_runlock (int /*<<< orphan*/ *,struct rm_priotracker*) ; 

void
osd_del(u_int type, struct osd *osd, u_int slot)
{
	struct rm_priotracker tracker;

	rm_rlock(&osdm[type].osd_object_lock, &tracker);
	do_osd_del(type, osd, slot, 0);
	rm_runlock(&osdm[type].osd_object_lock, &tracker);
}