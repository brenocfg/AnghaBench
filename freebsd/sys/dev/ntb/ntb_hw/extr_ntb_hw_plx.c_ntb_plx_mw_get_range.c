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
typedef  scalar_t__ vm_paddr_t ;
struct ntb_plx_softc {unsigned int mw_count; unsigned int b2b_mw; size_t b2b_off; unsigned int split; size_t alut; struct ntb_plx_mw_info* mw_info; } ;
struct ntb_plx_mw_info {int mw_bar; size_t mw_size; scalar_t__ mw_64bit; scalar_t__ mw_vbase; scalar_t__ mw_pbase; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int ntb_plx_user_mw_to_idx (struct ntb_plx_softc*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int
ntb_plx_mw_get_range(device_t dev, unsigned mw_idx, vm_paddr_t *base,
    caddr_t *vbase, size_t *size, size_t *align, size_t *align_size,
    bus_addr_t *plimit)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);
	struct ntb_plx_mw_info *mw;
	size_t off, ss;
	unsigned sp, split;

	mw_idx = ntb_plx_user_mw_to_idx(sc, mw_idx, &sp);
	if (mw_idx >= sc->mw_count)
		return (EINVAL);
	off = 0;
	if (mw_idx == sc->b2b_mw) {
		KASSERT(sc->b2b_off != 0,
		    ("user shouldn't get non-shared b2b mw"));
		off = sc->b2b_off;
	}
	mw = &sc->mw_info[mw_idx];
	split = (mw->mw_bar == 2) ? sc->split : 0;
	ss = (mw->mw_size - off) >> split;

	/* Local to remote memory window parameters. */
	if (base != NULL)
		*base = mw->mw_pbase + off + ss * sp;
	if (vbase != NULL)
		*vbase = mw->mw_vbase + off + ss * sp;
	if (size != NULL)
		*size = ss;

	/*
	 * Remote to local memory window translation address alignment.
	 * Translation address has to be aligned to the BAR size, but A-LUT
	 * entries re-map addresses can be aligned to 1/128 or 1/256 of it.
	 * XXX: In B2B mode we can change BAR size (and so alignmet) live,
	 * but there is no way to report it here, so report safe value.
	 */
	if (align != NULL) {
		if (sc->alut && mw->mw_bar == 2)
			*align = (mw->mw_size - off) / 128 / sc->alut;
		else
			*align = mw->mw_size - off;
	}

	/*
	 * Remote to local memory window size alignment.
	 * The chip has no limit registers, but A-LUT, when available, allows
	 * access control with granularity of 1/128 or 1/256 of the BAR size.
	 * XXX: In B2B case we can change BAR size live, but there is no way
	 * to report it, so report half of the BAR size, that should be safe.
	 * In non-B2B case there is no control at all, so report the BAR size.
	 */
	if (align_size != NULL) {
		if (sc->alut && mw->mw_bar == 2)
			*align_size = (mw->mw_size - off) / 128 / sc->alut;
		else if (sc->b2b_mw >= 0)
			*align_size = (mw->mw_size - off) / 2;
		else
			*align_size = mw->mw_size - off;
	}

	/* Remote to local memory window translation address upper limit. */
	if (plimit != NULL)
		*plimit = mw->mw_64bit ? BUS_SPACE_MAXADDR :
		    BUS_SPACE_MAXADDR_32BIT;
	return (0);
}