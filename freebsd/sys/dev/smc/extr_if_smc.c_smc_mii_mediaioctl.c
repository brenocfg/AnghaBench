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
typedef  int /*<<< orphan*/  u_long ;
struct smc_softc {int /*<<< orphan*/  smc_ifp; int /*<<< orphan*/ * smc_miibus; } ;
struct mii_data {int /*<<< orphan*/  mii_media; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ *) ; 
 int ifmedia_ioctl (int /*<<< orphan*/ ,struct ifreq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smc_mii_mediaioctl(struct smc_softc *sc, struct ifreq *ifr, u_long command)
{
	struct mii_data	*mii;

	if (sc->smc_miibus == NULL)
		return (EINVAL);

	mii = device_get_softc(sc->smc_miibus);
	return (ifmedia_ioctl(sc->smc_ifp, ifr, &mii->mii_media, command));
}