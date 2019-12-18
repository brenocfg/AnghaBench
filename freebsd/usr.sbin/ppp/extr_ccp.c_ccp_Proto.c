#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_8__ {TYPE_3__* bundle; int /*<<< orphan*/  link; } ;
struct ccp {TYPE_4__ fsm; } ;
struct TYPE_5__ {int /*<<< orphan*/  active; } ;
struct TYPE_6__ {TYPE_1__ mp; } ;
struct TYPE_7__ {TYPE_2__ ncp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROTO_COMPD ; 
 int /*<<< orphan*/  PROTO_ICOMPD ; 
 int /*<<< orphan*/  link2physical (int /*<<< orphan*/ ) ; 

u_short
ccp_Proto(struct ccp *ccp)
{
  return !link2physical(ccp->fsm.link) || !ccp->fsm.bundle->ncp.mp.active ?
         PROTO_COMPD : PROTO_ICOMPD;
}