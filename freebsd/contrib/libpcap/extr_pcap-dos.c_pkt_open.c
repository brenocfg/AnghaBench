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
struct device {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  PKT_RX_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  PDRX_ALL_PACKETS ; 
 int /*<<< orphan*/  PDRX_BROADCAST ; 
 int /*<<< orphan*/  PktInitDriver (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PktQueueBusy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PktResetStatistics (int /*<<< orphan*/ ) ; 
 TYPE_1__ pktInfo ; 

__attribute__((used)) static int pkt_open (struct device *dev)
{
  PKT_RX_MODE mode;

  if (dev->flags & IFF_PROMISC)
       mode = PDRX_ALL_PACKETS;
  else mode = PDRX_BROADCAST;

  if (!PktInitDriver(mode))
     return (0);

  PktResetStatistics (pktInfo.handle);
  PktQueueBusy (FALSE);
  return (1);
}