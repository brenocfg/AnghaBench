#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fsm {int dummy; } ;
struct TYPE_5__ {size_t algorithm; int /*<<< orphan*/ * state; } ;
struct ccp {TYPE_2__ out; } ;
struct TYPE_4__ {int (* Reset ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_1__ o; } ;

/* Variables and functions */
 TYPE_3__** algorithm ; 
 struct ccp* fsm2ccp (struct fsm*) ; 
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
CcpRecvResetReq(struct fsm *fp)
{
  /* Got a reset REQ, reset outgoing dictionary */
  struct ccp *ccp = fsm2ccp(fp);
  if (ccp->out.state == NULL)
    return 1;
  return (*algorithm[ccp->out.algorithm]->o.Reset)(ccp->out.state);
}