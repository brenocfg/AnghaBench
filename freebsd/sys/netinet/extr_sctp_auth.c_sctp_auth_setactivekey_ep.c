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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  default_keyid; int /*<<< orphan*/  shared_keys; } ;
struct sctp_inpcb {TYPE_1__ sctp_ep; } ;
typedef  int /*<<< orphan*/  sctp_sharedkey_t ;

/* Variables and functions */
 int /*<<< orphan*/ * sctp_find_sharedkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
sctp_auth_setactivekey_ep(struct sctp_inpcb *inp, uint16_t keyid)
{
	sctp_sharedkey_t *skey;

	/* find the key */
	skey = sctp_find_sharedkey(&inp->sctp_ep.shared_keys, keyid);
	if (skey == NULL) {
		/* that key doesn't exist */
		return (-1);
	}
	inp->sctp_ep.default_keyid = keyid;
	return (0);
}