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
struct cbb_softc {int /*<<< orphan*/  rl; int /*<<< orphan*/  dev; } ;
struct cbb_reslist {int /*<<< orphan*/  res; int /*<<< orphan*/  type; int /*<<< orphan*/  rid; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 struct cbb_reslist* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cbb_reslist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cbb_destroy_res(struct cbb_softc *sc)
{
	struct cbb_reslist *rle;

	while ((rle = SLIST_FIRST(&sc->rl)) != NULL) {
		device_printf(sc->dev, "Danger Will Robinson: Resource "
		    "left allocated!  This is a bug... "
		    "(rid=%x, type=%d, addr=%jx)\n", rle->rid, rle->type,
		    rman_get_start(rle->res));
		SLIST_REMOVE_HEAD(&sc->rl, link);
		free(rle, M_DEVBUF);
	}
}