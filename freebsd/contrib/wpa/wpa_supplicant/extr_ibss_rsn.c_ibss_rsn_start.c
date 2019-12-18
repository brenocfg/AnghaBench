#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct ibss_rsn_peer {int /*<<< orphan*/  own_auth_tx; int /*<<< orphan*/  authentication_status; } ;
struct ibss_rsn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBSS_RSN_AUTH_BY_US ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibss_rsn_peer*,int /*<<< orphan*/ *) ; 
 int ibss_rsn_auth_init (struct ibss_rsn*,struct ibss_rsn_peer*) ; 
 int /*<<< orphan*/  ibss_rsn_auth_timeout ; 
 struct ibss_rsn_peer* ibss_rsn_get_peer (struct ibss_rsn*,int /*<<< orphan*/  const*) ; 
 struct ibss_rsn_peer* ibss_rsn_peer_init (struct ibss_rsn*,int /*<<< orphan*/  const*) ; 
 int ibss_rsn_send_auth (struct ibss_rsn*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_get_reltime (int /*<<< orphan*/ *) ; 

int ibss_rsn_start(struct ibss_rsn *ibss_rsn, const u8 *addr)
{
	struct ibss_rsn_peer *peer;
	int res;

	if (!ibss_rsn)
		return -1;

	/* if the peer already exists, exit immediately */
	peer = ibss_rsn_get_peer(ibss_rsn, addr);
	if (peer)
		return 0;

	peer = ibss_rsn_peer_init(ibss_rsn, addr);
	if (peer == NULL)
		return -1;

	/* Open Authentication: send first Authentication frame */
	res = ibss_rsn_send_auth(ibss_rsn, addr, 1);
	if (res) {
		/*
		 * The driver may not support Authentication frame exchange in
		 * IBSS. Ignore authentication and go through EAPOL exchange.
		 */
		peer->authentication_status |= IBSS_RSN_AUTH_BY_US;
		return ibss_rsn_auth_init(ibss_rsn, peer);
	} else {
		os_get_reltime(&peer->own_auth_tx);
		eloop_register_timeout(1, 0, ibss_rsn_auth_timeout, peer, NULL);
	}

	return 0;
}