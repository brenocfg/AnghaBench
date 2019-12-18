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
struct ibss_rsn_peer {int authentication_status; } ;

/* Variables and functions */
 int IBSS_RSN_AUTH_BY_US ; 
 int IBSS_RSN_AUTH_EAPOL_BY_US ; 

__attribute__((used)) static int ibss_rsn_is_auth_started(struct ibss_rsn_peer * peer)
{
	return peer->authentication_status &
	       (IBSS_RSN_AUTH_BY_US | IBSS_RSN_AUTH_EAPOL_BY_US);
}