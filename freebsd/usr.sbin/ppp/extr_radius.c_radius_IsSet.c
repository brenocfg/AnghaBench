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
struct TYPE_2__ {int fd; } ;
struct radius {TYPE_1__ cx; } ;
struct fdescriptor {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/  const*) ; 
 struct radius* descriptor2radius (struct fdescriptor*) ; 

__attribute__((used)) static int
radius_IsSet(struct fdescriptor *d, const fd_set *fdset)
{
  struct radius *r = descriptor2radius(d);

  return r && r->cx.fd != -1 && FD_ISSET(r->cx.fd, fdset);
}