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
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int num_algo; scalar_t__* hmac; } ;
typedef  TYPE_1__ sctp_hmaclist_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ SCTP_AUTH_HMAC_ID_RSVD ; 
 int /*<<< orphan*/  SCTP_DEBUG_AUTH1 ; 

uint16_t
sctp_negotiate_hmacid(sctp_hmaclist_t *peer, sctp_hmaclist_t *local)
{
	int i, j;

	if ((local == NULL) || (peer == NULL))
		return (SCTP_AUTH_HMAC_ID_RSVD);

	for (i = 0; i < peer->num_algo; i++) {
		for (j = 0; j < local->num_algo; j++) {
			if (peer->hmac[i] == local->hmac[j]) {
				/* found the "best" one */
				SCTPDBG(SCTP_DEBUG_AUTH1,
				    "SCTP: negotiated peer HMAC id %u\n",
				    peer->hmac[i]);
				return (peer->hmac[i]);
			}
		}
	}
	/* didn't find one! */
	return (SCTP_AUTH_HMAC_ID_RSVD);
}