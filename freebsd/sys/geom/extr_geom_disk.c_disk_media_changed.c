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
struct g_provider {int dummy; } ;
struct g_geom {int /*<<< orphan*/  provider; } ;
struct disk {struct g_geom* d_geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct g_provider* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_NEXT (struct g_provider*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_media_changed (struct g_provider*,int) ; 
 int /*<<< orphan*/  provider ; 

void
disk_media_changed(struct disk *dp, int flag)
{
	struct g_geom *gp;
	struct g_provider *pp;

	gp = dp->d_geom;
	if (gp != NULL) {
		pp = LIST_FIRST(&gp->provider);
		if (pp != NULL) {
			KASSERT(LIST_NEXT(pp, provider) == NULL,
			    ("geom %p has more than one provider", gp));
			g_media_changed(pp, flag);
		}
	}
}