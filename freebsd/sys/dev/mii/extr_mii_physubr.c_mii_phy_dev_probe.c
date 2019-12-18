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
struct mii_phydesc {int /*<<< orphan*/  mpd_name; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mii_phydesc* mii_phy_match (int /*<<< orphan*/ ,struct mii_phydesc const*) ; 

int
mii_phy_dev_probe(device_t dev, const struct mii_phydesc *mpd, int mrv)
{

	mpd = mii_phy_match(device_get_ivars(dev), mpd);
	if (mpd != NULL) {
		device_set_desc(dev, mpd->mpd_name);
		return (mrv);
	}
	return (ENXIO);
}