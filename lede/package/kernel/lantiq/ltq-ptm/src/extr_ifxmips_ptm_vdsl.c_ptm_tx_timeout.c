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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int,char*) ; 
 int /*<<< orphan*/  IFX_REG_W32_MASK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBOX_IGU1_IER ; 
 struct net_device** g_net_dev ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void ptm_tx_timeout(struct net_device *dev)
{
    ASSERT(dev == g_net_dev[0], "incorrect device");

    /*  disable TX irq, release skb when sending new packet */
    IFX_REG_W32_MASK(1 << 17, 0, MBOX_IGU1_IER);

    /*  wake up TX queue    */
    netif_wake_queue(dev);

    return;
}