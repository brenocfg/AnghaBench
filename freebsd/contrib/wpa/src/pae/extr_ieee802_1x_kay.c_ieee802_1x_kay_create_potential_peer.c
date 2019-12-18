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
struct ieee802_1x_mka_participant {int /*<<< orphan*/  potential_peers; } ;
struct ieee802_1x_kay_peer {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  dl_list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ieee802_1x_kay_peer* ieee802_1x_kay_create_peer (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee802_1x_kay_dump_peer (struct ieee802_1x_kay_peer*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct ieee802_1x_kay_peer *
ieee802_1x_kay_create_potential_peer(
	struct ieee802_1x_mka_participant *participant, const u8 *mi, u32 mn)
{
	struct ieee802_1x_kay_peer *peer;

	peer = ieee802_1x_kay_create_peer(mi, mn);
	if (!peer)
		return NULL;

	dl_list_add(&participant->potential_peers, &peer->list);

	wpa_printf(MSG_DEBUG, "KaY: Potential peer created");
	ieee802_1x_kay_dump_peer(peer);

	return peer;
}