#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_6__ {int majorRev; } ;
struct TYPE_7__ {TYPE_1__ fmRevInfo; } ;
struct TYPE_9__ {scalar_t__ macId; scalar_t__ addr; TYPE_3__* p_DtsecDriverParam; int /*<<< orphan*/  f_Event; int /*<<< orphan*/  f_Exception; TYPE_2__ fmMacControllerDriver; int /*<<< orphan*/  enetMode; } ;
typedef  TYPE_4__ t_Dtsec ;
struct TYPE_8__ {int preamble_len; scalar_t__ rx_prepend; scalar_t__ non_back_to_back_ipg1; scalar_t__ non_back_to_back_ipg2; scalar_t__ back_to_back_ipg; scalar_t__ halfdup_alt_backoff_val; scalar_t__ halfdup_retransmit; scalar_t__ halfdup_coll_window; scalar_t__ tbipa; scalar_t__ rx_len_check; scalar_t__ rx_ctrl_acc; scalar_t__ rx_flow; scalar_t__ rx_time_stamp_en; scalar_t__ tx_time_stamp_en; scalar_t__ halfdup_on; scalar_t__ rx_preamble; scalar_t__ tx_preamble; scalar_t__ loopback; } ;

/* Variables and functions */
 scalar_t__ ENET_SPEED_FROM_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_NOT_IN_RANGE ; 
 int /*<<< orphan*/  E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FM_MAX_NUM_OF_1G_MACS ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ MAX_COLLISION_WINDOW ; 
 scalar_t__ MAX_INTER_PACKET_GAP ; 
 scalar_t__ MAX_INTER_PALTERNATE_BEB ; 
 scalar_t__ MAX_PACKET_ALIGNMENT ; 
 scalar_t__ MAX_PHYS ; 
 scalar_t__ MAX_RETRANSMISSION ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ e_ENET_SPEED_1000 ; 
 scalar_t__ e_ENET_SPEED_10000 ; 

__attribute__((used)) static t_Error CheckInitParameters(t_Dtsec *p_Dtsec)
{
    if (ENET_SPEED_FROM_MODE(p_Dtsec->enetMode) >= e_ENET_SPEED_10000)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Ethernet 1G MAC driver only supports 1G or lower speeds"));
    if (p_Dtsec->macId >= FM_MAX_NUM_OF_1G_MACS)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("macId can not be greater than the number of 1G MACs"));
    if (p_Dtsec->addr == 0)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Ethernet MAC Must have a valid MAC Address"));
    if ((ENET_SPEED_FROM_MODE(p_Dtsec->enetMode) >= e_ENET_SPEED_1000) &&
        p_Dtsec->p_DtsecDriverParam->halfdup_on)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Ethernet MAC 1G can't work in half duplex"));
    if (p_Dtsec->p_DtsecDriverParam->halfdup_on && (p_Dtsec->p_DtsecDriverParam)->loopback)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("LoopBack is not supported in halfDuplex mode"));
#ifdef FM_RX_PREAM_4_ERRATA_DTSEC_A001
    if (p_Dtsec->fmMacControllerDriver.fmRevInfo.majorRev <= 6) /* fixed for rev3 */
        if (p_Dtsec->p_DtsecDriverParam->rx_preamble)
            RETURN_ERROR(MAJOR, E_NOT_SUPPORTED, ("preambleRxEn"));
#endif /* FM_RX_PREAM_4_ERRATA_DTSEC_A001 */
    if (((p_Dtsec->p_DtsecDriverParam)->tx_preamble || (p_Dtsec->p_DtsecDriverParam)->rx_preamble) &&( (p_Dtsec->p_DtsecDriverParam)->preamble_len != 0x7))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Preamble length should be 0x7 bytes"));
    if ((p_Dtsec->p_DtsecDriverParam)->halfdup_on &&
       (p_Dtsec->p_DtsecDriverParam->tx_time_stamp_en || p_Dtsec->p_DtsecDriverParam->rx_time_stamp_en))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("dTSEC in half duplex mode has to be with 1588 timeStamping diable"));
    if ((p_Dtsec->p_DtsecDriverParam)->rx_flow && (p_Dtsec->p_DtsecDriverParam)->rx_ctrl_acc )
        RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Receive control frame are not passed to the system memory so it can not be accept "));
    if ((p_Dtsec->p_DtsecDriverParam)->rx_prepend  > MAX_PACKET_ALIGNMENT)
        RETURN_ERROR(MAJOR, E_INVALID_STATE, ("packetAlignmentPadding can't be greater than %d ",MAX_PACKET_ALIGNMENT ));
    if (((p_Dtsec->p_DtsecDriverParam)->non_back_to_back_ipg1  > MAX_INTER_PACKET_GAP) ||
        ((p_Dtsec->p_DtsecDriverParam)->non_back_to_back_ipg2 > MAX_INTER_PACKET_GAP) ||
        ((p_Dtsec->p_DtsecDriverParam)->back_to_back_ipg > MAX_INTER_PACKET_GAP))
        RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Inter packet gap can't be greater than %d ",MAX_INTER_PACKET_GAP ));
    if ((p_Dtsec->p_DtsecDriverParam)->halfdup_alt_backoff_val > MAX_INTER_PALTERNATE_BEB)
        RETURN_ERROR(MAJOR, E_INVALID_STATE, ("alternateBackoffVal can't be greater than %d ",MAX_INTER_PALTERNATE_BEB ));
    if ((p_Dtsec->p_DtsecDriverParam)->halfdup_retransmit > MAX_RETRANSMISSION)
        RETURN_ERROR(MAJOR, E_INVALID_STATE, ("maxRetransmission can't be greater than %d ",MAX_RETRANSMISSION ));
    if ((p_Dtsec->p_DtsecDriverParam)->halfdup_coll_window > MAX_COLLISION_WINDOW)
        RETURN_ERROR(MAJOR, E_INVALID_STATE, ("collisionWindow can't be greater than %d ",MAX_COLLISION_WINDOW ));

    /*  If Auto negotiation process is disabled, need to */
    /*  Set up the PHY using the MII Management Interface */
    if (p_Dtsec->p_DtsecDriverParam->tbipa > MAX_PHYS)
        RETURN_ERROR(MAJOR, E_NOT_IN_RANGE, ("PHY address (should be 0-%d)", MAX_PHYS));
    if (!p_Dtsec->f_Exception)
        RETURN_ERROR(MAJOR, E_INVALID_HANDLE, ("uninitialized f_Exception"));
    if (!p_Dtsec->f_Event)
        RETURN_ERROR(MAJOR, E_INVALID_HANDLE, ("uninitialized f_Event"));

#ifdef FM_LEN_CHECK_ERRATA_FMAN_SW002
    if (p_Dtsec->p_DtsecDriverParam->rx_len_check)
       RETURN_ERROR(MINOR, E_NOT_SUPPORTED, ("LengthCheck!"));
#endif /* FM_LEN_CHECK_ERRATA_FMAN_SW002 */

    return E_OK;
}