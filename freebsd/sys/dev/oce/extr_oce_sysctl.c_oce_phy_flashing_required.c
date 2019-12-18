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
struct oce_phy_info {scalar_t__ phy_type; scalar_t__ interface_type; } ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PHY_TYPE_BASET_10GB ; 
 scalar_t__ TN_8022 ; 
 int /*<<< orphan*/  TRUE ; 
 int oce_mbox_get_phy_info (int /*<<< orphan*/ ,struct oce_phy_info*) ; 

__attribute__((used)) static boolean_t
oce_phy_flashing_required(POCE_SOFTC sc)
{
	int status = 0;
	struct oce_phy_info phy_info;

	status = oce_mbox_get_phy_info(sc, &phy_info);
	if (status)
		return FALSE;

	if ((phy_info.phy_type == TN_8022) &&
		(phy_info.interface_type == PHY_TYPE_BASET_10GB)) {
		return TRUE;
	}

	return FALSE;
}