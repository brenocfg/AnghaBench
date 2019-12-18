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
struct mgb_softc {int dummy; } ;

/* Variables and functions */
 int mgb_dmac_reset (struct mgb_softc*) ; 
 int mgb_hw_reset (struct mgb_softc*) ; 
 int /*<<< orphan*/  mgb_mac_init (struct mgb_softc*) ; 
 int mgb_phy_reset (struct mgb_softc*) ; 

__attribute__((used)) static int
mgb_hw_init(struct mgb_softc *sc)
{
	int error = 0;

	error = mgb_hw_reset(sc);
	if (error != 0)
		goto fail;

	mgb_mac_init(sc);

	error = mgb_phy_reset(sc);
	if (error != 0)
		goto fail;

	error = mgb_dmac_reset(sc);
	if (error != 0)
		goto fail;

fail:
	return error;
}