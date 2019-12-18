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
struct mii_phydesc {scalar_t__ mpd_oui; scalar_t__ mpd_model; int /*<<< orphan*/ * mpd_name; } ;
struct mii_attach_args {int /*<<< orphan*/  mii_id2; int /*<<< orphan*/  mii_id1; } ;

/* Variables and functions */
 scalar_t__ MII_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ MII_OUI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const struct mii_phydesc *
mii_phy_match_gen(const struct mii_attach_args *ma,
  const struct mii_phydesc *mpd, size_t len)
{

	for (; mpd->mpd_name != NULL;
	    mpd = (const struct mii_phydesc *)((const char *)mpd + len)) {
		if (MII_OUI(ma->mii_id1, ma->mii_id2) == mpd->mpd_oui &&
		    MII_MODEL(ma->mii_id2) == mpd->mpd_model)
			return (mpd);
	}
	return (NULL);
}