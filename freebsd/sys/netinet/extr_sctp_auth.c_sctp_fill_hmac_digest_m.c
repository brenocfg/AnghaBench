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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {scalar_t__ assoc_keyid; int /*<<< orphan*/ * assoc_key; int /*<<< orphan*/  peer_random; int /*<<< orphan*/  random; } ;
struct TYPE_6__ {TYPE_1__ authinfo; int /*<<< orphan*/  peer_hmac_id; int /*<<< orphan*/  shared_keys; } ;
struct sctp_tcb {TYPE_2__ asoc; } ;
struct sctp_auth_chunk {int /*<<< orphan*/  hmac; int /*<<< orphan*/  shared_key_id; } ;
struct mbuf {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * key; } ;
typedef  TYPE_3__ sctp_sharedkey_t ;
typedef  int /*<<< orphan*/  sctp_key_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ SCTP_AUTH_DEBUG ; 
 int /*<<< orphan*/  SCTP_DEBUG_AUTH1 ; 
 int /*<<< orphan*/  SCTP_SIZE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sctp_compute_hashkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_compute_hmac_m (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* sctp_find_sharedkey (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sctp_free_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_get_hmac_digest_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_print_key (int /*<<< orphan*/ *,char*) ; 

void
sctp_fill_hmac_digest_m(struct mbuf *m, uint32_t auth_offset,
    struct sctp_auth_chunk *auth, struct sctp_tcb *stcb, uint16_t keyid)
{
	uint32_t digestlen;
	sctp_sharedkey_t *skey;
	sctp_key_t *key;

	if ((stcb == NULL) || (auth == NULL))
		return;

	/* zero the digest + chunk padding */
	digestlen = sctp_get_hmac_digest_len(stcb->asoc.peer_hmac_id);
	memset(auth->hmac, 0, SCTP_SIZE32(digestlen));

	/* is the desired key cached? */
	if ((keyid != stcb->asoc.authinfo.assoc_keyid) ||
	    (stcb->asoc.authinfo.assoc_key == NULL)) {
		if (stcb->asoc.authinfo.assoc_key != NULL) {
			/* free the old cached key */
			sctp_free_key(stcb->asoc.authinfo.assoc_key);
		}
		skey = sctp_find_sharedkey(&stcb->asoc.shared_keys, keyid);
		/* the only way skey is NULL is if null key id 0 is used */
		if (skey != NULL)
			key = skey->key;
		else
			key = NULL;
		/* compute a new assoc key and cache it */
		stcb->asoc.authinfo.assoc_key =
		    sctp_compute_hashkey(stcb->asoc.authinfo.random,
		    stcb->asoc.authinfo.peer_random, key);
		stcb->asoc.authinfo.assoc_keyid = keyid;
		SCTPDBG(SCTP_DEBUG_AUTH1, "caching key id %u\n",
		    stcb->asoc.authinfo.assoc_keyid);
#ifdef SCTP_DEBUG
		if (SCTP_AUTH_DEBUG)
			sctp_print_key(stcb->asoc.authinfo.assoc_key,
			    "Assoc Key");
#endif
	}

	/* set in the active key id */
	auth->shared_key_id = htons(keyid);

	/* compute and fill in the digest */
	(void)sctp_compute_hmac_m(stcb->asoc.peer_hmac_id, stcb->asoc.authinfo.assoc_key,
	    m, auth_offset, auth->hmac);
}