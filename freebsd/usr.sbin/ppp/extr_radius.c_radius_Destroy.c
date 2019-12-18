#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fd; int /*<<< orphan*/  rad; int /*<<< orphan*/  timer; } ;
struct TYPE_3__ {scalar_t__ sendkeylen; int /*<<< orphan*/ * sendkey; scalar_t__ recvkeylen; int /*<<< orphan*/ * recvkey; } ;
struct radius {TYPE_2__ cx; TYPE_1__ mppe; int /*<<< orphan*/ * errstr; int /*<<< orphan*/ * ipv6prefix; int /*<<< orphan*/ * repstr; int /*<<< orphan*/ * msrepstr; int /*<<< orphan*/ * filterid; int /*<<< orphan*/  ipv6routes; int /*<<< orphan*/  routes; scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rad_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  route_DeleteAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

void
radius_Destroy(struct radius *r)
{
  r->valid = 0;
  log_Printf(LogDEBUG, "Radius: radius_Destroy\n");
  timer_Stop(&r->cx.timer);
  route_DeleteAll(&r->routes);
#ifndef NOINET6
  route_DeleteAll(&r->ipv6routes);
#endif
  free(r->filterid);
  r->filterid = NULL;
  free(r->msrepstr);
  r->msrepstr = NULL;
  free(r->repstr);
  r->repstr = NULL;
#ifndef NOINET6
  free(r->ipv6prefix);
  r->ipv6prefix = NULL;
#endif
  free(r->errstr);
  r->errstr = NULL;
  free(r->mppe.recvkey);
  r->mppe.recvkey = NULL;
  r->mppe.recvkeylen = 0;
  free(r->mppe.sendkey);
  r->mppe.sendkey = NULL;
  r->mppe.sendkeylen = 0;
  if (r->cx.fd != -1) {
    r->cx.fd = -1;
    rad_close(r->cx.rad);
  }
}