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
struct mii_data {int dummy; } ;
struct awg_softc {int /*<<< orphan*/  miibus; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_LOCK (struct awg_softc*) ; 
 int /*<<< orphan*/  AWG_UNLOCK (struct awg_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 struct awg_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static int
awg_media_change(if_t ifp)
{
	struct awg_softc *sc;
	struct mii_data *mii;
	int error;

	sc = if_getsoftc(ifp);
	mii = device_get_softc(sc->miibus);

	AWG_LOCK(sc);
	error = mii_mediachg(mii);
	AWG_UNLOCK(sc);

	return (error);
}