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
struct TYPE_7__ {size_t algorithm; } ;
struct TYPE_5__ {scalar_t__ state; } ;
struct ccp {TYPE_3__ out; TYPE_1__ fsm; } ;
struct TYPE_6__ {int MTUOverhead; } ;
struct TYPE_8__ {TYPE_2__ o; } ;

/* Variables and functions */
 scalar_t__ ST_OPENED ; 
 TYPE_4__** algorithm ; 

int
ccp_MTUOverhead(struct ccp *ccp)
{
  if (ccp->fsm.state == ST_OPENED && ccp->out.algorithm >= 0)
    return algorithm[ccp->out.algorithm]->o.MTUOverhead;

  return 0;
}