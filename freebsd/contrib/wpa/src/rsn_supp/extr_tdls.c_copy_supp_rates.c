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
struct wpa_tdls_peer {int /*<<< orphan*/  supp_rates; int /*<<< orphan*/  supp_rates_len; } ;
struct wpa_eapol_ie_parse {scalar_t__ ext_supp_rates_len; int /*<<< orphan*/ * ext_supp_rates; scalar_t__ supp_rates_len; scalar_t__ supp_rates; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  merge_byte_arrays (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int copy_supp_rates(const struct wpa_eapol_ie_parse *kde,
			   struct wpa_tdls_peer *peer)
{
	if (!kde->supp_rates) {
		wpa_printf(MSG_DEBUG, "TDLS: No supported rates received");
		return -1;
	}
	peer->supp_rates_len = merge_byte_arrays(
		peer->supp_rates, sizeof(peer->supp_rates),
		kde->supp_rates + 2, kde->supp_rates_len - 2,
		kde->ext_supp_rates ? kde->ext_supp_rates + 2 : NULL,
		kde->ext_supp_rates ? kde->ext_supp_rates_len - 2 : 0);
	return 0;
}