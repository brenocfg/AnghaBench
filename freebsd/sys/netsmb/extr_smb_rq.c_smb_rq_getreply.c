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
struct mdchain {int dummy; } ;
struct smb_rq {struct mdchain sr_rp; } ;

/* Variables and functions */

int
smb_rq_getreply(struct smb_rq *rqp, struct mdchain **mbpp)
{
	*mbpp = &rqp->sr_rp;
	return 0;
}