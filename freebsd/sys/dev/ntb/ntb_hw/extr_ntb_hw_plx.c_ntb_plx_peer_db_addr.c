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
typedef  int vm_size_t ;
typedef  scalar_t__ uint64_t ;
struct ntb_plx_softc {size_t b2b_mw; scalar_t__ link; int /*<<< orphan*/  conf_res; struct ntb_plx_mw_info* mw_info; } ;
struct ntb_plx_mw_info {scalar_t__ mw_pbase; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PLX_NTX_BASE (struct ntb_plx_softc*) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ntb_plx_peer_db_addr(device_t dev, bus_addr_t *db_addr, vm_size_t *db_size)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);
	struct ntb_plx_mw_info *mw;

	KASSERT((db_addr != NULL && db_size != NULL), ("must be non-NULL"));

	if (sc->b2b_mw >= 0) {
		mw = &sc->mw_info[sc->b2b_mw];
		*db_addr = (uint64_t)mw->mw_pbase + PLX_NTX_BASE(sc) + 0xc4c;
	} else {
		*db_addr = rman_get_start(sc->conf_res) + PLX_NTX_BASE(sc);
		*db_addr += sc->link ? 0xc4c : 0xc5c;
	}
	*db_size = 4;
	return (0);
}