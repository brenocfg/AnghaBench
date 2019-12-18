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
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 int /*<<< orphan*/  SCU_SAS_PCFG_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_SAS_PCFG_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCU_SAS_PCFG_WRITE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUSPEND_PROTOCOL_ENGINE ; 
 int /*<<< orphan*/  scic_sds_phy_setup_transport (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void scic_sds_phy_suspend(
   SCIC_SDS_PHY_T * this_phy
)
{
   U32 scu_sas_pcfg_value;

   scu_sas_pcfg_value = SCU_SAS_PCFG_READ(this_phy);
   scu_sas_pcfg_value |= SCU_SAS_PCFG_GEN_BIT(SUSPEND_PROTOCOL_ENGINE);
   SCU_SAS_PCFG_WRITE(this_phy, scu_sas_pcfg_value);

   scic_sds_phy_setup_transport(
      this_phy, SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX
   );
}