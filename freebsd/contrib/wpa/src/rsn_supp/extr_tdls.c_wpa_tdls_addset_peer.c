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
struct wpa_tdls_peer {int /*<<< orphan*/  supp_oper_classes_len; int /*<<< orphan*/  supp_oper_classes; int /*<<< orphan*/  supp_channels_len; int /*<<< orphan*/  supp_channels; int /*<<< orphan*/  ext_capab_len; int /*<<< orphan*/  ext_capab; int /*<<< orphan*/  wmm_capable; int /*<<< orphan*/  qos_info; int /*<<< orphan*/  vht_capabilities; int /*<<< orphan*/  ht_capabilities; int /*<<< orphan*/  supp_rates_len; int /*<<< orphan*/  supp_rates; int /*<<< orphan*/  capability; int /*<<< orphan*/  aid; int /*<<< orphan*/  addr; } ;
struct wpa_sm {int dummy; } ;

/* Variables and functions */
 int wpa_sm_tdls_peer_addset (struct wpa_sm*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_tdls_addset_peer(struct wpa_sm *sm, struct wpa_tdls_peer *peer,
				int add)
{
	return wpa_sm_tdls_peer_addset(sm, peer->addr, add, peer->aid,
				       peer->capability,
				       peer->supp_rates, peer->supp_rates_len,
				       peer->ht_capabilities,
				       peer->vht_capabilities,
				       peer->qos_info, peer->wmm_capable,
				       peer->ext_capab, peer->ext_capab_len,
				       peer->supp_channels,
				       peer->supp_channels_len,
				       peer->supp_oper_classes,
				       peer->supp_oper_classes_len);
}