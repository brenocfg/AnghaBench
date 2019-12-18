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
struct ttydevice {int /*<<< orphan*/  hook; } ;
struct physical {int /*<<< orphan*/  fd; int /*<<< orphan*/  handler; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int NgSendData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,size_t) ; 
 struct ttydevice* device2tty (int /*<<< orphan*/ ) ; 
 scalar_t__ isngtty (struct ttydevice*) ; 
 int write (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static ssize_t
tty_Write(struct physical *p, const void *v, size_t n)
{
  struct ttydevice *dev = device2tty(p->handler);

  if (isngtty(dev))
    return NgSendData(p->fd, dev->hook, v, n) == -1 ? -1 : (ssize_t)n;
  else
    return write(p->fd, v, n);
}