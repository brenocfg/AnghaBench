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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  reqid; } ;
struct lcp {TYPE_1__ fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE_PROTOREJ ; 
 int /*<<< orphan*/  MB_LCPOUT ; 
 int /*<<< orphan*/  fsm_Output (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
lcp_SendProtoRej(struct lcp *lcp, u_char *option, int count)
{
  /* Don't understand `option' */
  fsm_Output(&lcp->fsm, CODE_PROTOREJ, lcp->fsm.reqid, option, count,
             MB_LCPOUT);
}