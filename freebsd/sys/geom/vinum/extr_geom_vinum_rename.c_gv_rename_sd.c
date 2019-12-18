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
struct gv_softc {int dummy; } ;
struct gv_sd {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int GV_ERR_INVNAME ; 
 int GV_ERR_NAMETAKEN ; 
 scalar_t__ GV_ERR_NOTFOUND ; 
 int /*<<< orphan*/  G_VINUM_DEBUG (int,char*,char*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gv_object_type (struct gv_softc*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
gv_rename_sd(struct gv_softc *sc, struct gv_sd *s, char *newname, int flags)
{
	char *dot1, *dot2;

	KASSERT(s != NULL, ("gv_rename_sd: NULL s"));

	if (gv_object_type(sc, newname) != GV_ERR_NOTFOUND) {
		G_VINUM_DEBUG(1, "subdisk name %s already in use", newname);
		return (GV_ERR_NAMETAKEN);
	}

	/* Locate the sd number part of the sd names. */
	dot1 = strchr(newname, '.');
	if (dot1 == NULL || (dot2 = strchr(dot1 +  1, '.')) == NULL) {
		G_VINUM_DEBUG(0, "proposed sd name '%s' is not a valid sd name",
		    newname);
		return (GV_ERR_INVNAME);
	}
	strlcpy(s->name, newname, sizeof(s->name));
	return (0);
}