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
struct net_device_stats {int dummy; } ;
struct device {int /*<<< orphan*/  priv; int /*<<< orphan*/ * release_rx_buf; int /*<<< orphan*/ * peek_rx_buf; int /*<<< orphan*/ * get_rx_buf; int /*<<< orphan*/  copy_rx_buf; int /*<<< orphan*/  get_stats; int /*<<< orphan*/  close; int /*<<< orphan*/  xmit; int /*<<< orphan*/  open; } ;

/* Variables and functions */
 int /*<<< orphan*/  PktReceive ; 
 int /*<<< orphan*/  PktSearchDriver () ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int /*<<< orphan*/  pkt_close ; 
 int /*<<< orphan*/  pkt_open ; 
 int /*<<< orphan*/  pkt_stats ; 
 int /*<<< orphan*/  pkt_xmit ; 

__attribute__((used)) static int pkt_probe (struct device *dev)
{
  if (!PktSearchDriver())
     return (0);

  dev->open           = pkt_open;
  dev->xmit           = pkt_xmit;
  dev->close          = pkt_close;
  dev->get_stats      = pkt_stats;
  dev->copy_rx_buf    = PktReceive;  /* farmem peek and copy routine */
  dev->get_rx_buf     = NULL;
  dev->peek_rx_buf    = NULL;
  dev->release_rx_buf = NULL;
  dev->priv           = calloc (sizeof(struct net_device_stats), 1);
  if (!dev->priv)
     return (0);
  return (1);
}