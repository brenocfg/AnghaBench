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
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ active_keyid; } ;
struct TYPE_6__ {int /*<<< orphan*/  shared_keys; TYPE_1__ authinfo; } ;
struct sctp_tcb {TYPE_2__ asoc; } ;
struct TYPE_7__ {int refcount; int deactivated; } ;
typedef  TYPE_3__ sctp_sharedkey_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_NOTIFY_AUTH_FREE_KEY ; 
 int /*<<< orphan*/  SCTP_SO_LOCKED ; 
 TYPE_3__* sctp_find_sharedkey (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sctp_ulp_notify (int /*<<< orphan*/ ,struct sctp_tcb*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sctp_deact_sharedkey(struct sctp_tcb *stcb, uint16_t keyid)
{
	sctp_sharedkey_t *skey;

	if (stcb == NULL)
		return (-1);

	/* is the keyid the assoc active sending key */
	if (keyid == stcb->asoc.authinfo.active_keyid)
		return (-1);

	/* does the key exist? */
	skey = sctp_find_sharedkey(&stcb->asoc.shared_keys, keyid);
	if (skey == NULL)
		return (-1);

	/* are there other refcount holders on the key? */
	if (skey->refcount == 1) {
		/* no other users, send a notification for this key */
		sctp_ulp_notify(SCTP_NOTIFY_AUTH_FREE_KEY, stcb, keyid, 0,
		    SCTP_SO_LOCKED);
	}

	/* mark the key as deactivated */
	skey->deactivated = 1;

	return (0);
}