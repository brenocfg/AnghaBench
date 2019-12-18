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
struct ibss_rsn_peer {int /*<<< orphan*/  supp; int /*<<< orphan*/  auth; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct ibss_rsn_peer*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibss_rsn_auth_timeout ; 
 int /*<<< orphan*/  os_free (struct ibss_rsn_peer*) ; 
 int /*<<< orphan*/  wpa_auth_sta_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_deinit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ibss_rsn_free(struct ibss_rsn_peer *peer)
{
	eloop_cancel_timeout(ibss_rsn_auth_timeout, peer, NULL);
	wpa_auth_sta_deinit(peer->auth);
	wpa_sm_deinit(peer->supp);
	os_free(peer);
}