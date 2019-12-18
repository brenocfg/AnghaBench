#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct net_device {int dummy; } ;
struct ifreq {scalar_t__ ifr_data; } ;
struct TYPE_10__ {int rx_eth_crc_present; int rx_eth_crc_check; int rx_tc_crc_check; int rx_tc_crc_len; int tx_eth_crc_gen; int tx_tc_crc_gen; int tx_tc_crc_len; } ;
struct TYPE_9__ {int /*<<< orphan*/  wtx_total_pdu; scalar_t__ wrx_len_violation_drop_pdu; scalar_t__ wrx_nodesc_drop_pdu; int /*<<< orphan*/  wrx_tccrc_err_pdu; int /*<<< orphan*/  wrx_correct_pdu; int /*<<< orphan*/  wrx_err_cw; int /*<<< orphan*/  wrx_idle_cw; int /*<<< orphan*/  wrx_nonidle_cw; } ;
struct TYPE_8__ {int RxEthCrcPresent; int RxEthCrcCheck; int RxTcCrcCheck; int RxTcCrcLen; int TxEthCrcGen; int TxTcCrcGen; int TxTcCrcLen; } ;
struct TYPE_7__ {int /*<<< orphan*/  ifTxIdleCodewords; int /*<<< orphan*/  ifTxNoIdleCodewords; int /*<<< orphan*/  ifRxCodingViolation; int /*<<< orphan*/  ifRxIdleCodewords; int /*<<< orphan*/  ifRxNoIdleCodewords; } ;
struct TYPE_6__ {int /*<<< orphan*/  TxSend; scalar_t__ RxDropped; int /*<<< orphan*/  TC_CrcError; int /*<<< orphan*/  RxCorrect; } ;
typedef  TYPE_1__ PTM_FRAME_MIB_T ;
typedef  TYPE_2__ PTM_CW_IF_ENTRY_T ;
typedef  TYPE_3__ IFX_PTM_CFG_T ;

/* Variables and functions */
 int ARRAY_SIZE (struct net_device**) ; 
 int /*<<< orphan*/  ASSERT (int,char*,int) ; 
 TYPE_5__* CFG_ETH_EFMTC_CRC ; 
 int EOPNOTSUPP ; 
#define  IFX_PTM_CFG_GET 131 
#define  IFX_PTM_CFG_SET 130 
#define  IFX_PTM_MIB_CW_GET 129 
#define  IFX_PTM_MIB_FRAME_GET 128 
 TYPE_4__* WAN_MIB_TABLE ; 
 struct net_device** g_net_dev ; 

__attribute__((used)) static int ptm_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
    int ndev;

    for ( ndev = 0; ndev < ARRAY_SIZE(g_net_dev) && g_net_dev[ndev] != dev; ndev++ );
    ASSERT(ndev >= 0 && ndev < ARRAY_SIZE(g_net_dev), "ndev = %d (wrong value)", ndev);

    switch ( cmd )
    {
    case IFX_PTM_MIB_CW_GET:
        ((PTM_CW_IF_ENTRY_T *)ifr->ifr_data)->ifRxNoIdleCodewords   = WAN_MIB_TABLE[ndev].wrx_nonidle_cw;
        ((PTM_CW_IF_ENTRY_T *)ifr->ifr_data)->ifRxIdleCodewords     = WAN_MIB_TABLE[ndev].wrx_idle_cw;
        ((PTM_CW_IF_ENTRY_T *)ifr->ifr_data)->ifRxCodingViolation   = WAN_MIB_TABLE[ndev].wrx_err_cw;
        ((PTM_CW_IF_ENTRY_T *)ifr->ifr_data)->ifTxNoIdleCodewords   = 0;
        ((PTM_CW_IF_ENTRY_T *)ifr->ifr_data)->ifTxIdleCodewords     = 0;
        break;
    case IFX_PTM_MIB_FRAME_GET:
        ((PTM_FRAME_MIB_T *)ifr->ifr_data)->RxCorrect   = WAN_MIB_TABLE[ndev].wrx_correct_pdu;
        ((PTM_FRAME_MIB_T *)ifr->ifr_data)->TC_CrcError = WAN_MIB_TABLE[ndev].wrx_tccrc_err_pdu;
        ((PTM_FRAME_MIB_T *)ifr->ifr_data)->RxDropped   = WAN_MIB_TABLE[ndev].wrx_nodesc_drop_pdu + WAN_MIB_TABLE[ndev].wrx_len_violation_drop_pdu;
        ((PTM_FRAME_MIB_T *)ifr->ifr_data)->TxSend      = WAN_MIB_TABLE[ndev].wtx_total_pdu;
        break;
    case IFX_PTM_CFG_GET:
        ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxEthCrcPresent = CFG_ETH_EFMTC_CRC->rx_eth_crc_present;
        ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxEthCrcCheck   = CFG_ETH_EFMTC_CRC->rx_eth_crc_check;
        ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxTcCrcCheck    = CFG_ETH_EFMTC_CRC->rx_tc_crc_check;
        ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxTcCrcLen      = CFG_ETH_EFMTC_CRC->rx_tc_crc_len;
        ((IFX_PTM_CFG_T *)ifr->ifr_data)->TxEthCrcGen     = CFG_ETH_EFMTC_CRC->tx_eth_crc_gen;
        ((IFX_PTM_CFG_T *)ifr->ifr_data)->TxTcCrcGen      = CFG_ETH_EFMTC_CRC->tx_tc_crc_gen;
        ((IFX_PTM_CFG_T *)ifr->ifr_data)->TxTcCrcLen      = CFG_ETH_EFMTC_CRC->tx_tc_crc_len;
        break;
    case IFX_PTM_CFG_SET:
        CFG_ETH_EFMTC_CRC->rx_eth_crc_present   = ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxEthCrcPresent ? 1 : 0;
        CFG_ETH_EFMTC_CRC->rx_eth_crc_check     = ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxEthCrcCheck ? 1 : 0;
        if ( ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxTcCrcCheck && (((IFX_PTM_CFG_T *)ifr->ifr_data)->RxTcCrcLen == 16 || ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxTcCrcLen == 32) )
        {
            CFG_ETH_EFMTC_CRC->rx_tc_crc_check  = 1;
            CFG_ETH_EFMTC_CRC->rx_tc_crc_len    = ((IFX_PTM_CFG_T *)ifr->ifr_data)->RxTcCrcLen;
        }
        else
        {
            CFG_ETH_EFMTC_CRC->rx_tc_crc_check  = 0;
            CFG_ETH_EFMTC_CRC->rx_tc_crc_len    = 0;
        }
        CFG_ETH_EFMTC_CRC->tx_eth_crc_gen       = ((IFX_PTM_CFG_T *)ifr->ifr_data)->TxEthCrcGen ? 1 : 0;
        if ( ((IFX_PTM_CFG_T *)ifr->ifr_data)->TxTcCrcGen && (((IFX_PTM_CFG_T *)ifr->ifr_data)->TxTcCrcLen == 16 || ((IFX_PTM_CFG_T *)ifr->ifr_data)->TxTcCrcLen == 32) )
        {
            CFG_ETH_EFMTC_CRC->tx_tc_crc_gen    = 1;
            CFG_ETH_EFMTC_CRC->tx_tc_crc_len    = ((IFX_PTM_CFG_T *)ifr->ifr_data)->TxTcCrcLen;
        }
        else
        {
            CFG_ETH_EFMTC_CRC->tx_tc_crc_gen    = 0;
            CFG_ETH_EFMTC_CRC->tx_tc_crc_len    = 0;
        }
        break;
    default:
        return -EOPNOTSUPP;
    }

    return 0;
}