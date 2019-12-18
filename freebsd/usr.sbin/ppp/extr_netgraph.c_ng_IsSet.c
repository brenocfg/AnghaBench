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
struct ngdevice {scalar_t__ cs; } ;
struct fdescriptor {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/  const*) ; 
 struct physical* descriptor2physical (struct fdescriptor*) ; 
 struct ngdevice* device2ng (int /*<<< orphan*/ ) ; 
 scalar_t__ physical_IsSet (struct fdescriptor*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
ng_IsSet(struct fdescriptor *d, const fd_set *fdset)
{
  struct physical *p = descriptor2physical(d);
  struct ngdevice *dev = device2ng(p->handler);
  int result;

  result = dev->cs >= 0 && FD_ISSET(dev->cs, fdset);
  result += physical_IsSet(d, fdset);

  return result;
}