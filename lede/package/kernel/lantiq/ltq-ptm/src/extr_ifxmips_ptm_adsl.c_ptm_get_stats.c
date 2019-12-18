#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device_stats {scalar_t__ rx_packets; scalar_t__ rx_dropped; scalar_t__ rx_errors; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ wrx_correct_pdu; scalar_t__ wrx_len_violation_drop_pdu; scalar_t__ wrx_nodesc_drop_pdu; scalar_t__ wrx_ethcrc_err_pdu; scalar_t__ wrx_tccrc_err_pdu; } ;
struct TYPE_5__ {TYPE_1__* itf; } ;
struct TYPE_4__ {struct net_device_stats stats; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct net_device**) ; 
 int /*<<< orphan*/  ASSERT (int,char*,int) ; 
 TYPE_3__* WAN_MIB_TABLE ; 
 struct net_device** g_net_dev ; 
 TYPE_2__ g_ptm_priv_data ; 

__attribute__((used)) static struct net_device_stats *ptm_get_stats(struct net_device *dev)
{
    int ndev;

    for ( ndev = 0; ndev < ARRAY_SIZE(g_net_dev) && g_net_dev[ndev] != dev; ndev++ );
    ASSERT(ndev >= 0 && ndev < ARRAY_SIZE(g_net_dev), "ndev = %d (wrong value)", ndev);

    g_ptm_priv_data.itf[ndev].stats.rx_errors   = WAN_MIB_TABLE[ndev].wrx_tccrc_err_pdu + WAN_MIB_TABLE[ndev].wrx_ethcrc_err_pdu;
    g_ptm_priv_data.itf[ndev].stats.rx_dropped  = WAN_MIB_TABLE[ndev].wrx_nodesc_drop_pdu + WAN_MIB_TABLE[ndev].wrx_len_violation_drop_pdu + (WAN_MIB_TABLE[ndev].wrx_correct_pdu - g_ptm_priv_data.itf[ndev].stats.rx_packets);

    return &g_ptm_priv_data.itf[ndev].stats;
}