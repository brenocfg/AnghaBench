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
struct TYPE_2__ {int mb_count; } ;
struct smb_rq {int* sr_wcount; TYPE_1__ sr_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBERROR (char*) ; 

void
smb_rq_wend(struct smb_rq *rqp)
{
	if (rqp->sr_wcount == NULL) {
		SMBERROR("no wcount\n");	/* actually panic */
		return;
	}
	if (rqp->sr_rq.mb_count & 1)
		SMBERROR("odd word count\n");
	*rqp->sr_wcount = rqp->sr_rq.mb_count / 2;
}