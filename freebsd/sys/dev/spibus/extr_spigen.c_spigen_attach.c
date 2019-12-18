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
struct spigen_softc {int /*<<< orphan*/ * sc_cdev; int /*<<< orphan*/  sc_adev; int /*<<< orphan*/  sc_mtx; void* sc_dev; } ;
struct make_dev_args {int mda_mode; int mda_unit; void* mda_si_drv1; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_cr; int /*<<< orphan*/ * mda_devsw; int /*<<< orphan*/  mda_flags; } ;
typedef  void* device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GID_OPERATOR ; 
 int /*<<< orphan*/  MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int SPIBUS_CS_HIGH ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (void*) ; 
 void* device_get_parent (void*) ; 
 struct spigen_softc* device_get_softc (void*) ; 
 int device_get_unit (void*) ; 
 int make_dev_alias_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ **,char*,int,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spibus_get_cs (void*,int*) ; 
 int /*<<< orphan*/  spigen_cdevsw ; 

__attribute__((used)) static int
spigen_attach(device_t dev)
{
	struct spigen_softc *sc;
	const int unit = device_get_unit(dev);
	int cs, res;
	struct make_dev_args mda;

	spibus_get_cs(dev, &cs);
	cs &= ~SPIBUS_CS_HIGH; /* trim 'cs high' bit */

	sc = device_get_softc(dev);
	sc->sc_dev = dev;

	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL, MTX_DEF);

	make_dev_args_init(&mda);
	mda.mda_flags = MAKEDEV_WAITOK;
	mda.mda_devsw = &spigen_cdevsw;
	mda.mda_cr = NULL;
	mda.mda_uid = UID_ROOT;
	mda.mda_gid = GID_OPERATOR;
	mda.mda_mode = 0660;
	mda.mda_unit = unit;
	mda.mda_si_drv1 = dev;

	res = make_dev_s(&mda, &(sc->sc_cdev), "spigen%d.%d",
	    device_get_unit(device_get_parent(dev)), cs);
	if (res) {
		return res;
	}

#ifdef SPIGEN_LEGACY_CDEVNAME
	res = make_dev_alias_p(0, &sc->sc_adev, sc->sc_cdev, "spigen%d", unit);
	if (res) {
		if (sc->sc_cdev) {
			destroy_dev(sc->sc_cdev);
			sc->sc_cdev = NULL;
		}
		return res;
	}
#endif

	return (0);
}