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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_TCI_NCQ_MAPPING_TABLE ; 
 int /*<<< orphan*/  SCU_STPTLDARNI_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_TLCR_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_TLCR_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCU_TLCR_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void scic_sds_phy_setup_transport(
   SCIC_SDS_PHY_T * this_phy,
   U32              device_id
)
{
   U32 tl_control;

   SCU_STPTLDARNI_WRITE(this_phy, device_id);

   // The read should guarntee that the first write gets posted
   // before the next write
   tl_control = SCU_TLCR_READ(this_phy);
   tl_control |= SCU_TLCR_GEN_BIT(CLEAR_TCI_NCQ_MAPPING_TABLE);
   SCU_TLCR_WRITE(this_phy, tl_control);
}