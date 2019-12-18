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
struct fdescriptor {int dummy; } ;
struct execdevice {scalar_t__ fd_out; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/  const*) ; 
 struct physical* descriptor2physical (struct fdescriptor*) ; 
 struct execdevice* device2exec (int /*<<< orphan*/ ) ; 
 scalar_t__ physical_IsSet (struct fdescriptor*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
exec_IsSet(struct fdescriptor *d, const fd_set *fdset)
{
  struct physical *p = descriptor2physical(d);
  struct execdevice *dev = device2exec(p->handler);
  int result = dev->fd_out >= 0 && FD_ISSET(dev->fd_out, fdset);
  result += physical_IsSet(d, fdset);

  return result;
}