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
struct mbchain {int dummy; } ;
struct smb_rq {struct mbchain sr_rq; } ;

/* Variables and functions */

int
smb_rq_getrequest(struct smb_rq *rqp, struct mbchain **mbpp)
{
	*mbpp = &rqp->sr_rq;
	return 0;
}