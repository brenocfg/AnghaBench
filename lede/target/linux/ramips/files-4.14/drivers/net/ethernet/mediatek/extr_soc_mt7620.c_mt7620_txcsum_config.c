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

/* Variables and functions */
 int CDMA_ICS_EN ; 
 int CDMA_TCS_EN ; 
 int CDMA_UCS_EN ; 
 int /*<<< orphan*/  MT7620A_CDMA_CSG_CFG ; 
 int fe_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fe_w32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7620_txcsum_config(bool enable)
{
	if (enable)
		fe_w32(fe_r32(MT7620A_CDMA_CSG_CFG) | (CDMA_ICS_EN |
					CDMA_UCS_EN | CDMA_TCS_EN),
				MT7620A_CDMA_CSG_CFG);
	else
		fe_w32(fe_r32(MT7620A_CDMA_CSG_CFG) & ~(CDMA_ICS_EN |
					CDMA_UCS_EN | CDMA_TCS_EN),
				MT7620A_CDMA_CSG_CFG);
}