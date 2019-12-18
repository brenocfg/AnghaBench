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
struct mpserver {scalar_t__ fd; } ;
struct fdescriptor {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (scalar_t__,int /*<<< orphan*/  const*) ; 
 struct mpserver* descriptor2mpserver (struct fdescriptor*) ; 

__attribute__((used)) static int
mpserver_IsSet(struct fdescriptor *d, const fd_set *fdset)
{
  struct mpserver *s = descriptor2mpserver(d);
  return s->fd >= 0 && FD_ISSET(s->fd, fdset);
}