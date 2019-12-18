#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * key; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ sctp_sharedkey_t ;

/* Variables and functions */
 scalar_t__ SCTP_DECREMENT_AND_CHECK_REFCOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCTP_FREE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_M_AUTH_KY ; 
 int /*<<< orphan*/  sctp_free_key (int /*<<< orphan*/ *) ; 

void
sctp_free_sharedkey(sctp_sharedkey_t *skey)
{
	if (skey == NULL)
		return;

	if (SCTP_DECREMENT_AND_CHECK_REFCOUNT(&skey->refcount)) {
		if (skey->key != NULL)
			sctp_free_key(skey->key);
		SCTP_FREE(skey, SCTP_M_AUTH_KY);
	}
}