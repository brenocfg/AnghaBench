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
struct g_provider {struct g_geom* geom; } ;
struct g_geom {int /*<<< orphan*/  consumer; } ;
struct g_consumer {scalar_t__ acw; } ;

/* Variables and functions */
 int EROFS ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct g_consumer* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int g_access (struct g_consumer*,int,int,int) ; 

__attribute__((used)) static int
g_uzip_access(struct g_provider *pp, int dr, int dw, int de)
{
	struct g_geom *gp;
	struct g_consumer *cp;

	gp = pp->geom;
	cp = LIST_FIRST(&gp->consumer);
	KASSERT (cp != NULL, ("g_uzip_access but no consumer"));

	if (cp->acw + dw > 0)
		return (EROFS);

	return (g_access(cp, dr, dw, de));
}