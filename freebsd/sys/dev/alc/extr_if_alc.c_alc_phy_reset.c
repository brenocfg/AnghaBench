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
struct alc_softc {int alc_flags; } ;

/* Variables and functions */
 int ALC_FLAG_AR816X_FAMILY ; 
 int /*<<< orphan*/  alc_phy_reset_813x (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_phy_reset_816x (struct alc_softc*) ; 

__attribute__((used)) static void
alc_phy_reset(struct alc_softc *sc)
{

	if ((sc->alc_flags & ALC_FLAG_AR816X_FAMILY) != 0)
		alc_phy_reset_816x(sc);
	else
		alc_phy_reset_813x(sc);
}