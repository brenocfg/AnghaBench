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
typedef  int uint16_t ;
struct bwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct bwn_mac {struct bwn_softc* mac_sc; } ;

/* Variables and functions */
 int BHND_IOCTL_CLK_FORCE ; 
 int BWN_IOCTL_PHYRESET ; 
 int BWN_IOCTL_SUPPORT_G ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int bhnd_write_ioctl (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
bwn_phy_reset(struct bwn_mac *mac)
{
	struct bwn_softc	*sc;
	uint16_t		 iost, mask;
	int			 error;

	sc = mac->mac_sc;

	iost = BWN_IOCTL_PHYRESET | BHND_IOCTL_CLK_FORCE;
	mask = iost | BWN_IOCTL_SUPPORT_G;

	if ((error = bhnd_write_ioctl(sc->sc_dev, iost, mask)))
		return (error);

	DELAY(1000);

	iost &= ~BHND_IOCTL_CLK_FORCE;

	if ((error = bhnd_write_ioctl(sc->sc_dev, iost, mask)))
		return (error);

	DELAY(1000);

	return (0);
}