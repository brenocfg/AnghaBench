#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ time_t ;
struct TYPE_5__ {int /*<<< orphan*/  port; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  mn; int /*<<< orphan*/  mi; } ;
struct ieee802_1x_mka_participant {TYPE_2__ current_peer_sci; TYPE_1__ current_peer_id; int /*<<< orphan*/  mi; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; int /*<<< orphan*/  addr; } ;
struct ieee802_1x_mka_basic_body {scalar_t__ version; int /*<<< orphan*/  priority; scalar_t__ key_server; int /*<<< orphan*/  macsec_capability; int /*<<< orphan*/  macsec_desired; int /*<<< orphan*/  actor_mn; int /*<<< orphan*/  actor_mi; TYPE_3__ actor_sci; int /*<<< orphan*/  ckn; } ;
struct ieee802_1x_kay_peer {scalar_t__ expire; scalar_t__ mn; int /*<<< orphan*/  key_server_priority; void* is_key_server; int /*<<< orphan*/  macsec_capability; int /*<<< orphan*/  macsec_desired; } ;
struct ieee802_1x_kay {scalar_t__ is_obliged_key_server; } ;
typedef  void* Boolean ;

/* Variables and functions */
 int MI_LEN ; 
 int MKA_HDR_LEN ; 
 double MKA_HELLO_TIME ; 
 scalar_t__ MKA_VERSION_ID ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ be_to_host32 (int /*<<< orphan*/ ) ; 
 size_t get_mka_param_body_len (struct ieee802_1x_mka_basic_body const*) ; 
 struct ieee802_1x_kay_peer* ieee802_1x_kay_create_potential_peer (struct ieee802_1x_mka_participant*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ieee802_1x_mka_participant* ieee802_1x_kay_get_participant (struct ieee802_1x_kay*,int /*<<< orphan*/ ,size_t) ; 
 struct ieee802_1x_kay_peer* ieee802_1x_kay_get_peer (struct ieee802_1x_mka_participant*,int /*<<< orphan*/ ) ; 
 struct ieee802_1x_kay_peer* ieee802_1x_kay_get_peer_sci (struct ieee802_1x_mka_participant*,TYPE_3__*) ; 
 int /*<<< orphan*/  mi_txt (int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reset_participant_mi (struct ieee802_1x_mka_participant*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct ieee802_1x_mka_participant *
ieee802_1x_mka_decode_basic_body(struct ieee802_1x_kay *kay, const u8 *mka_msg,
				 size_t msg_len)
{
	struct ieee802_1x_mka_participant *participant;
	const struct ieee802_1x_mka_basic_body *body;
	struct ieee802_1x_kay_peer *peer;
	size_t ckn_len;
	size_t body_len;

	body = (const struct ieee802_1x_mka_basic_body *) mka_msg;

	if (body->version > MKA_VERSION_ID) {
		wpa_printf(MSG_DEBUG,
			   "KaY: Peer's version(%d) greater than MKA current version(%d)",
			   body->version, MKA_VERSION_ID);
	}
	if (kay->is_obliged_key_server && body->key_server) {
		wpa_printf(MSG_DEBUG, "KaY: I must be key server - ignore MKPDU claiming to be from a key server");
		return NULL;
	}

	body_len = get_mka_param_body_len(body);
	if (body_len < sizeof(struct ieee802_1x_mka_basic_body) - MKA_HDR_LEN) {
		wpa_printf(MSG_DEBUG, "KaY: Too small body length %zu",
			   body_len);
		return NULL;
	}
	ckn_len = body_len -
	    (sizeof(struct ieee802_1x_mka_basic_body) - MKA_HDR_LEN);
	participant = ieee802_1x_kay_get_participant(kay, body->ckn, ckn_len);
	if (!participant) {
		wpa_printf(MSG_DEBUG,
			   "KaY: Peer is not included in my CA - ignore MKPDU");
		return NULL;
	}

	/* If the peer's MI is my MI, I will choose new MI */
	if (os_memcmp(body->actor_mi, participant->mi, MI_LEN) == 0) {
		if (!reset_participant_mi(participant))
			return NULL;
		wpa_printf(MSG_DEBUG,
			   "KaY: Peer using my MI - selected a new random MI: %s",
			   mi_txt(participant->mi));
	}

	os_memcpy(participant->current_peer_id.mi, body->actor_mi, MI_LEN);
	participant->current_peer_id.mn = body->actor_mn;
	os_memcpy(participant->current_peer_sci.addr, body->actor_sci.addr,
		  sizeof(participant->current_peer_sci.addr));
	participant->current_peer_sci.port = body->actor_sci.port;

	/* handler peer */
	peer = ieee802_1x_kay_get_peer(participant, body->actor_mi);
	if (!peer) {
		/* Check duplicated SCI
		 *
		 * A duplicated SCI indicates either an active attacker or
		 * a valid peer whose MI is being changed. The latter scenario
		 * is more likely because to have gotten this far the received
		 * MKPDU must have had a valid ICV, indicating the peer holds
		 * the same CAK as our participant.
		 *
		 * Before creating a new peer object for the new MI we must
		 * clean up the resources (SCs and SAs) associated with the
		 * old peer. An easy way to do this is to ignore MKPDUs with
		 * the new MI's for now and just wait for the old peer to
		 * time out and clean itself up (within MKA_LIFE_TIME).
		 *
		 * This method is preferable to deleting the old peer here
		 * and now and continuing on with processing because if this
		 * MKPDU is from an attacker it's better to ignore the MKPDU
		 * than to process it (and delete a valid peer as well).
		 */
		peer = ieee802_1x_kay_get_peer_sci(participant,
						   &body->actor_sci);
		if (peer) {
			time_t new_expire;

			wpa_printf(MSG_WARNING,
				   "KaY: duplicated SCI detected - maybe active attacker or peer selected new MI - ignore MKPDU");
			/* Reduce timeout to speed up this process but left the
			 * chance for old one to prove aliveness. */
			new_expire = time(NULL) + MKA_HELLO_TIME * 1.5 / 1000;
			if (peer->expire > new_expire)
				peer->expire = new_expire;
			return NULL;
		}

		peer = ieee802_1x_kay_create_potential_peer(
			participant, body->actor_mi,
			be_to_host32(body->actor_mn));
		if (!peer) {
			wpa_printf(MSG_DEBUG,
				   "KaY: No potential peer entry found - ignore MKPDU");
			return NULL;
		}

		peer->macsec_desired = body->macsec_desired;
		peer->macsec_capability = body->macsec_capability;
		peer->is_key_server = (Boolean) body->key_server;
		peer->key_server_priority = body->priority;
	} else if (peer->mn < be_to_host32(body->actor_mn)) {
		peer->mn = be_to_host32(body->actor_mn);
		peer->macsec_desired = body->macsec_desired;
		peer->macsec_capability = body->macsec_capability;
		peer->is_key_server = (Boolean) body->key_server;
		peer->key_server_priority = body->priority;
	} else {
		wpa_printf(MSG_WARNING,
			   "KaY: The peer MN did not increase - ignore MKPDU");
		return NULL;
	}

	return participant;
}