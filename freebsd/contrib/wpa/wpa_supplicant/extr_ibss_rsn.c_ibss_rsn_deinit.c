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
struct ibss_rsn_peer {struct ibss_rsn_peer* next; } ;
struct ibss_rsn {scalar_t__ auth_group; struct ibss_rsn_peer* peers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibss_rsn_free (struct ibss_rsn_peer*) ; 
 int /*<<< orphan*/  os_free (struct ibss_rsn*) ; 
 int /*<<< orphan*/  wpa_deinit (scalar_t__) ; 

void ibss_rsn_deinit(struct ibss_rsn *ibss_rsn)
{
	struct ibss_rsn_peer *peer, *prev;

	if (ibss_rsn == NULL)
		return;

	peer = ibss_rsn->peers;
	while (peer) {
		prev = peer;
		peer = peer->next;
		ibss_rsn_free(prev);
	}

	if (ibss_rsn->auth_group)
		wpa_deinit(ibss_rsn->auth_group);
	os_free(ibss_rsn);

}