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
struct physical {int /*<<< orphan*/  handler; } ;
struct etherdevice {scalar_t__ connected; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 scalar_t__ CARRIER_LOST ; 
 scalar_t__ CARRIER_OK ; 
 scalar_t__ CARRIER_PENDING ; 
 struct etherdevice* device2ether (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_MessageIn (struct etherdevice*) ; 

__attribute__((used)) static int
ether_AwaitCarrier(struct physical *p)
{
  struct etherdevice *dev = device2ether(p->handler);

  if (dev->connected != CARRIER_OK && !dev->timeout--)
    dev->connected = CARRIER_LOST;
  else if (dev->connected == CARRIER_PENDING)
    ether_MessageIn(dev);

  return dev->connected;
}