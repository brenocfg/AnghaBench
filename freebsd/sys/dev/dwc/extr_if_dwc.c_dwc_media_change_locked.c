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
struct dwc_softc {int /*<<< orphan*/  mii_softc; } ;

/* Variables and functions */
 int mii_mediachg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dwc_media_change_locked(struct dwc_softc *sc)
{

	return (mii_mediachg(sc->mii_softc));
}