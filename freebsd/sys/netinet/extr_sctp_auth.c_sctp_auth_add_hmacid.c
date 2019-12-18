#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {int num_algo; int max_algo; scalar_t__* hmac; } ;
typedef  TYPE_1__ sctp_hmaclist_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ SCTP_AUTH_HMAC_ID_SHA1 ; 
 scalar_t__ SCTP_AUTH_HMAC_ID_SHA256 ; 
 int /*<<< orphan*/  SCTP_DEBUG_AUTH1 ; 

int
sctp_auth_add_hmacid(sctp_hmaclist_t *list, uint16_t hmac_id)
{
	int i;

	if (list == NULL)
		return (-1);
	if (list->num_algo == list->max_algo) {
		SCTPDBG(SCTP_DEBUG_AUTH1,
		    "SCTP: HMAC id list full, ignoring add %u\n", hmac_id);
		return (-1);
	}
	if ((hmac_id != SCTP_AUTH_HMAC_ID_SHA1) &&
	    (hmac_id != SCTP_AUTH_HMAC_ID_SHA256)) {
		return (-1);
	}
	/* Now is it already in the list */
	for (i = 0; i < list->num_algo; i++) {
		if (list->hmac[i] == hmac_id) {
			/* already in list */
			return (-1);
		}
	}
	SCTPDBG(SCTP_DEBUG_AUTH1, "SCTP: add HMAC id %u to list\n", hmac_id);
	list->hmac[list->num_algo++] = hmac_id;
	return (0);
}