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
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct ntb_plx_softc {unsigned int mw_count; struct ntb_plx_mw_info* mw_info; } ;
struct ntb_plx_mw_info {TYPE_1__* splits; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  mw_map_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 unsigned int ntb_plx_user_mw_to_idx (struct ntb_plx_softc*,unsigned int,unsigned int*) ; 

__attribute__((used)) static int
ntb_plx_mw_get_wc(device_t dev, unsigned mw_idx, vm_memattr_t *mode)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);
	struct ntb_plx_mw_info *mw;
	unsigned sp;

	mw_idx = ntb_plx_user_mw_to_idx(sc, mw_idx, &sp);
	if (mw_idx >= sc->mw_count)
		return (EINVAL);
	mw = &sc->mw_info[mw_idx];
	*mode = mw->splits[sp].mw_map_mode;
	return (0);
}