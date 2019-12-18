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
typedef  int /*<<< orphan*/  uint64_t ;
struct ntb_plx_softc {scalar_t__ b2b_mw; scalar_t__ link; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNTX_WRITE (struct ntb_plx_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTX_WRITE (struct ntb_plx_softc*,int,int /*<<< orphan*/ ) ; 
 struct ntb_plx_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ntb_plx_peer_db_set(device_t dev, uint64_t bit)
{
	struct ntb_plx_softc *sc = device_get_softc(dev);

	if (sc->b2b_mw >= 0)
		BNTX_WRITE(sc, 0xc4c, bit);
	else
		NTX_WRITE(sc, sc->link ? 0xc4c : 0xc5c, bit);
}