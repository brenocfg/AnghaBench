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
struct ieee802_1x_mka_participant {int /*<<< orphan*/  potential_peers; } ;
typedef  int Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Boolean
ieee802_1x_mka_potential_peer_body_present(
	struct ieee802_1x_mka_participant *participant)
{
	return !dl_list_empty(&participant->potential_peers);
}