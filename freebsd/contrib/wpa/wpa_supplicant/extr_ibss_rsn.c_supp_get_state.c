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
struct ibss_rsn_peer {int supp_state; } ;
typedef  enum wpa_states { ____Placeholder_wpa_states } wpa_states ;

/* Variables and functions */

__attribute__((used)) static enum wpa_states supp_get_state(void *ctx)
{
	struct ibss_rsn_peer *peer = ctx;
	return peer->supp_state;
}