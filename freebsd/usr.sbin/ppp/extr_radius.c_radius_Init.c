#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char* file; } ;
struct TYPE_11__ {scalar_t__ sendkeylen; int /*<<< orphan*/ * sendkey; scalar_t__ recvkeylen; int /*<<< orphan*/ * recvkey; scalar_t__ types; scalar_t__ policy; } ;
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_8__ {int fd; int /*<<< orphan*/ * auth; int /*<<< orphan*/  timer; int /*<<< orphan*/ * rad; } ;
struct TYPE_7__ {int /*<<< orphan*/  Write; int /*<<< orphan*/  Read; int /*<<< orphan*/  IsSet; int /*<<< orphan*/  UpdateSet; int /*<<< orphan*/  type; } ;
struct radius {TYPE_6__ cfg; TYPE_5__ mppe; int /*<<< orphan*/ * errstr; int /*<<< orphan*/ * ipv6routes; int /*<<< orphan*/ * ipv6prefix; int /*<<< orphan*/ * repstr; int /*<<< orphan*/ * msrepstr; int /*<<< orphan*/  mtu; int /*<<< orphan*/ * routes; TYPE_4__ mask; TYPE_3__ ip; scalar_t__ vj; scalar_t__ valid; TYPE_2__ cx; TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_MTU ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  INADDR_NONE ; 
 int /*<<< orphan*/  LogDEBUG ; 
 int /*<<< orphan*/  RADIUS_DESCRIPTOR ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,char,int) ; 
 int /*<<< orphan*/  radius_IsSet ; 
 int /*<<< orphan*/  radius_Read ; 
 int /*<<< orphan*/  radius_UpdateSet ; 
 int /*<<< orphan*/  radius_Write ; 

void
radius_Init(struct radius *r)
{
  r->desc.type = RADIUS_DESCRIPTOR;
  r->desc.UpdateSet = radius_UpdateSet;
  r->desc.IsSet = radius_IsSet;
  r->desc.Read = radius_Read;
  r->desc.Write = radius_Write;
  r->cx.fd = -1;
  r->cx.rad = NULL;
  memset(&r->cx.timer, '\0', sizeof r->cx.timer);
  r->cx.auth = NULL;
  r->valid = 0;
  r->vj = 0;
  r->ip.s_addr = INADDR_ANY;
  r->mask.s_addr = INADDR_NONE;
  r->routes = NULL;
  r->mtu = DEF_MTU;
  r->msrepstr = NULL;
  r->repstr = NULL;
#ifndef NOINET6
  r->ipv6prefix = NULL;
  r->ipv6routes = NULL;
#endif
  r->errstr = NULL;
  r->mppe.policy = 0;
  r->mppe.types = 0;
  r->mppe.recvkey = NULL;
  r->mppe.recvkeylen = 0;
  r->mppe.sendkey = NULL;
  r->mppe.sendkeylen = 0;
  *r->cfg.file = '\0';
  log_Printf(LogDEBUG, "Radius: radius_Init\n");
}