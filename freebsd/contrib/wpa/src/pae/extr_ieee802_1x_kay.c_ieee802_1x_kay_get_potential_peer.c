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
struct ieee802_1x_mka_participant {int /*<<< orphan*/  potential_peers; } ;
struct ieee802_1x_kay_peer {int dummy; } ;

/* Variables and functions */
 struct ieee802_1x_kay_peer* get_peer_mi (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static struct ieee802_1x_kay_peer *
ieee802_1x_kay_get_potential_peer(
	struct ieee802_1x_mka_participant *participant, const u8 *mi)
{
	return get_peer_mi(&participant->potential_peers, mi);
}