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
struct etherdevice {int cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 struct etherdevice* device2ether (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct etherdevice*) ; 
 int /*<<< orphan*/  physical_SetDescriptor (struct physical*) ; 

__attribute__((used)) static void
ether_Free(struct physical *p)
{
  struct etherdevice *dev = device2ether(p->handler);

  physical_SetDescriptor(p);
  if (dev->cs != -1)
    close(dev->cs);
  free(dev);
}