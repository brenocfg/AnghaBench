#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct iadev_priv {int carrier_detect; } ;
struct TYPE_2__ {int mb25_master_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  MB25_DIAG_CONTROL ; 
 int /*<<< orphan*/  MB25_INTR_STATUS ; 
 int MB25_IS_GSB ; 
 int /*<<< orphan*/  MB25_MASTER_CTRL ; 
 int MB25_MC_DREC ; 
 int MB25_MC_DRIC ; 
 int MB25_MC_ENABLED ; 
 int ia_phy_read32 (struct iadev_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia_phy_write32 (struct iadev_priv*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* mb25 ; 

__attribute__((used)) static void ia_mb25_init(struct iadev_priv *iadev)
{
#if 0
   mb25->mb25_master_ctrl = MB25_MC_DRIC | MB25_MC_DREC | MB25_MC_ENABLED;
#endif
	ia_phy_write32(iadev, MB25_MASTER_CTRL, MB25_MC_DRIC | MB25_MC_DREC);
	ia_phy_write32(iadev, MB25_DIAG_CONTROL, 0);

	iadev->carrier_detect =
		(ia_phy_read32(iadev, MB25_INTR_STATUS) & MB25_IS_GSB) ? 1 : 0;
}