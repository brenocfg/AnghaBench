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
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_2__ {scalar_t__ mb_count; } ;
struct smb_rq {TYPE_1__ sr_rq; int /*<<< orphan*/  sr_bcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb_reserve (TYPE_1__*,int) ; 

void
smb_rq_bstart(struct smb_rq *rqp)
{
	rqp->sr_bcount = mb_reserve(&rqp->sr_rq, sizeof(u_short));
	rqp->sr_rq.mb_count = 0;
}