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
struct bwi_softc {struct bwi_regwin* sc_cur_regwin; int /*<<< orphan*/  sc_dev; } ;
struct bwi_regwin {int /*<<< orphan*/  rw_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_REGWIN_EXIST (struct bwi_regwin*) ; 
 int EINVAL ; 
 int bwi_regwin_select (struct bwi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
bwi_regwin_switch(struct bwi_softc *sc, struct bwi_regwin *rw,
		  struct bwi_regwin **old_rw)
{
	int error;

	if (old_rw != NULL)
		*old_rw = NULL;

	if (!BWI_REGWIN_EXIST(rw))
		return EINVAL;

	if (sc->sc_cur_regwin != rw) {
		error = bwi_regwin_select(sc, rw->rw_id);
		if (error) {
			device_printf(sc->sc_dev, "can't select regwin %d\n",
				  rw->rw_id);
			return error;
		}
	}

	if (old_rw != NULL)
		*old_rw = sc->sc_cur_regwin;
	sc->sc_cur_regwin = rw;
	return 0;
}