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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct physical {int /*<<< orphan*/  dl; TYPE_1__ link; int /*<<< orphan*/  handler; } ;
struct fdescriptor {int dummy; } ;
struct etherdevice {scalar_t__ cs; scalar_t__ connected; } ;
struct bundle {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ CARRIER_LOST ; 
 int /*<<< orphan*/  CLOSE_NORMAL ; 
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  datalink_Down (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct physical* descriptor2physical (struct fdescriptor*) ; 
 struct etherdevice* device2ether (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_MessageIn (struct etherdevice*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physical_DescriptorRead (struct fdescriptor*,struct bundle*,int /*<<< orphan*/  const*) ; 
 scalar_t__ physical_IsSet (struct fdescriptor*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
ether_DescriptorRead(struct fdescriptor *d, struct bundle *bundle,
                     const fd_set *fdset)
{
  struct physical *p = descriptor2physical(d);
  struct etherdevice *dev = device2ether(p->handler);

  if (dev->cs >= 0 && FD_ISSET(dev->cs, fdset)) {
    ether_MessageIn(dev);
    if (dev->connected == CARRIER_LOST) {
      log_Printf(LogPHASE, "%s: Device disconnected\n", p->link.name);
      datalink_Down(p->dl, CLOSE_NORMAL);
      return;
    }
  }

  if (physical_IsSet(d, fdset))
    physical_DescriptorRead(d, bundle, fdset);
}