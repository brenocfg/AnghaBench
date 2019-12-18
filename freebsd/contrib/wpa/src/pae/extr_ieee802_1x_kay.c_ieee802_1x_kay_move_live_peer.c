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
typedef  int /*<<< orphan*/  u32 ;
struct receive_sc {int /*<<< orphan*/  list; scalar_t__ expire; int /*<<< orphan*/  mn; int /*<<< orphan*/  sci; } ;
struct ieee802_1x_mka_participant {int /*<<< orphan*/  rxsc_list; int /*<<< orphan*/  live_peers; int /*<<< orphan*/  kay; int /*<<< orphan*/  current_peer_sci; } ;
struct ieee802_1x_kay_peer {int /*<<< orphan*/  list; scalar_t__ expire; int /*<<< orphan*/  mn; int /*<<< orphan*/  sci; } ;

/* Variables and functions */
 int MKA_LIFE_TIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee802_1x_kay_dump_peer (struct receive_sc*) ; 
 struct receive_sc* ieee802_1x_kay_get_potential_peer (struct ieee802_1x_mka_participant*,int /*<<< orphan*/ *) ; 
 struct receive_sc* ieee802_1x_kay_init_receive_sc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct receive_sc*) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ secy_create_receive_sc (int /*<<< orphan*/ ,struct receive_sc*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct ieee802_1x_kay_peer *
ieee802_1x_kay_move_live_peer(struct ieee802_1x_mka_participant *participant,
			      u8 *mi, u32 mn)
{
	struct ieee802_1x_kay_peer *peer;
	struct receive_sc *rxsc;

	peer = ieee802_1x_kay_get_potential_peer(participant, mi);
	if (!peer)
		return NULL;

	rxsc = ieee802_1x_kay_init_receive_sc(&participant->current_peer_sci);
	if (!rxsc)
		return NULL;

	os_memcpy(&peer->sci, &participant->current_peer_sci,
		  sizeof(peer->sci));
	peer->mn = mn;
	peer->expire = time(NULL) + MKA_LIFE_TIME / 1000;

	wpa_printf(MSG_DEBUG, "KaY: Move potential peer to live peer");
	ieee802_1x_kay_dump_peer(peer);

	dl_list_del(&peer->list);
	if (secy_create_receive_sc(participant->kay, rxsc)) {
		wpa_printf(MSG_ERROR, "KaY: Can't create SC, discard peer");
		os_free(rxsc);
		os_free(peer);
		return NULL;
	}
	dl_list_add_tail(&participant->live_peers, &peer->list);

	dl_list_add(&participant->rxsc_list, &rxsc->list);

	return peer;
}