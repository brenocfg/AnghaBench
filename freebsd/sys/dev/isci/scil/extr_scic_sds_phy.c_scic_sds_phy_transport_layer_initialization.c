#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  U32 ;
struct TYPE_7__ {int /*<<< orphan*/ * transport_layer_registers; } ;
typedef  int /*<<< orphan*/  SCU_TRANSPORT_LAYER_REGISTERS_T ;
typedef  int /*<<< orphan*/  SCI_STATUS ;
typedef  TYPE_1__ SCIC_SDS_PHY_T ;

/* Variables and functions */
 int /*<<< orphan*/  SCIC_LOG_OBJECT_PHY ; 
 int /*<<< orphan*/  SCIC_LOG_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX ; 
 int /*<<< orphan*/  SCI_SUCCESS ; 
 int /*<<< orphan*/  SCU_STPTLDARNI_WRITE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_TLCR_GEN_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCU_TLCR_READ (TYPE_1__*) ; 
 int /*<<< orphan*/  SCU_TLCR_WRITE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STP_WRITE_DATA_PREFETCH ; 
 int /*<<< orphan*/  sci_base_object_get_logger (TYPE_1__*) ; 

__attribute__((used)) static
SCI_STATUS scic_sds_phy_transport_layer_initialization(
   SCIC_SDS_PHY_T                  *this_phy,
   SCU_TRANSPORT_LAYER_REGISTERS_T *transport_layer_registers
)
{
   U32 tl_control;

   SCIC_LOG_TRACE((
      sci_base_object_get_logger(this_phy),
      SCIC_LOG_OBJECT_PHY,
      "scic_sds_phy_link_layer_initialization(this_phy:0x%x, link_layer_registers:0x%x)\n",
      this_phy, transport_layer_registers
   ));

   this_phy->transport_layer_registers = transport_layer_registers;

   SCU_STPTLDARNI_WRITE(this_phy, SCIC_SDS_REMOTE_NODE_CONTEXT_INVALID_INDEX);

   // Hardware team recommends that we enable the STP prefetch for all transports
   tl_control = SCU_TLCR_READ(this_phy);
   tl_control |= SCU_TLCR_GEN_BIT(STP_WRITE_DATA_PREFETCH);
   SCU_TLCR_WRITE(this_phy, tl_control);

   return SCI_SUCCESS;
}