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
struct gv_volume {int plexcount; int /*<<< orphan*/  name; int /*<<< orphan*/  plexes; } ;
struct gv_plex {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct gv_plex* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int gv_start_plex (struct gv_plex*) ; 
 int gv_sync (struct gv_volume*) ; 

int
gv_start_vol(struct gv_volume *v)
{
	struct gv_plex *p;
	int error;

	KASSERT(v != NULL, ("gv_start_vol: NULL v"));

	error = 0;

	if (v->plexcount == 0)
		return (ENXIO);

	else if (v->plexcount == 1) {
		p = LIST_FIRST(&v->plexes);
		KASSERT(p != NULL, ("gv_start_vol: NULL p on %s", v->name));
		error = gv_start_plex(p);
	} else
		error = gv_sync(v);

	return (error);
}