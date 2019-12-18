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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ assoc_keyid; scalar_t__ recv_keyid; int /*<<< orphan*/ * recv_key; int /*<<< orphan*/ * assoc_key; } ;
struct TYPE_3__ {TYPE_2__ authinfo; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sctp_free_key (int /*<<< orphan*/ *) ; 

void
sctp_clear_cachedkeys(struct sctp_tcb *stcb, uint16_t keyid)
{
	if (stcb == NULL)
		return;

	if (keyid == stcb->asoc.authinfo.assoc_keyid) {
		sctp_free_key(stcb->asoc.authinfo.assoc_key);
		stcb->asoc.authinfo.assoc_key = NULL;
	}
	if (keyid == stcb->asoc.authinfo.recv_keyid) {
		sctp_free_key(stcb->asoc.authinfo.recv_key);
		stcb->asoc.authinfo.recv_key = NULL;
	}
}