#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  active_keyid; } ;
struct TYPE_6__ {TYPE_1__ authinfo; int /*<<< orphan*/  shared_keys; } ;
struct sctp_tcb {TYPE_2__ asoc; } ;
struct TYPE_7__ {int refcount; scalar_t__ deactivated; } ;
typedef  TYPE_3__ sctp_sharedkey_t ;

/* Variables and functions */
 TYPE_3__* sctp_find_sharedkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
sctp_auth_setactivekey(struct sctp_tcb *stcb, uint16_t keyid)
{
	sctp_sharedkey_t *skey = NULL;

	/* find the key on the assoc */
	skey = sctp_find_sharedkey(&stcb->asoc.shared_keys, keyid);
	if (skey == NULL) {
		/* that key doesn't exist */
		return (-1);
	}
	if ((skey->deactivated) && (skey->refcount > 1)) {
		/* can't reactivate a deactivated key with other refcounts */
		return (-1);
	}

	/* set the (new) active key */
	stcb->asoc.authinfo.active_keyid = keyid;
	/* reset the deactivated flag */
	skey->deactivated = 0;

	return (0);
}