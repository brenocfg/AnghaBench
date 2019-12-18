#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_state_machine {scalar_t__ wpa_key_mgmt; int /*<<< orphan*/  pairwise; int /*<<< orphan*/  ANonce; int /*<<< orphan*/  addr; TYPE_1__* wpa_auth; scalar_t__ dpp_z; int /*<<< orphan*/  pmk_r1_name; int /*<<< orphan*/  SNonce; int /*<<< orphan*/  pmk_r1_len; int /*<<< orphan*/  pmk_r1; scalar_t__ ft_completed; } ;
struct wpa_ptk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 scalar_t__ WPA_KEY_MGMT_DPP ; 
 int WPA_PMK_NAME_LEN ; 
 int wpa_auth_derive_ptk_ft (struct wpa_state_machine*,struct wpa_ptk*) ; 
 scalar_t__ wpa_key_mgmt_ft (scalar_t__) ; 
 int wpa_pmk_r1_to_ptk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_ptk*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int wpa_pmk_to_ptk (int /*<<< orphan*/  const*,unsigned int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,struct wpa_ptk*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * wpabuf_head (scalar_t__) ; 
 size_t wpabuf_len (scalar_t__) ; 

__attribute__((used)) static int wpa_derive_ptk(struct wpa_state_machine *sm, const u8 *snonce,
			  const u8 *pmk, unsigned int pmk_len,
			  struct wpa_ptk *ptk)
{
	const u8 *z = NULL;
	size_t z_len = 0;

#ifdef CONFIG_IEEE80211R_AP
	if (wpa_key_mgmt_ft(sm->wpa_key_mgmt)) {
		if (sm->ft_completed) {
			u8 ptk_name[WPA_PMK_NAME_LEN];

			return wpa_pmk_r1_to_ptk(sm->pmk_r1, sm->pmk_r1_len,
						 sm->SNonce, sm->ANonce,
						 sm->addr, sm->wpa_auth->addr,
						 sm->pmk_r1_name,
						 ptk, ptk_name,
						 sm->wpa_key_mgmt,
						 sm->pairwise);
		}
		return wpa_auth_derive_ptk_ft(sm, ptk);
	}
#endif /* CONFIG_IEEE80211R_AP */

#ifdef CONFIG_DPP2
	if (sm->wpa_key_mgmt == WPA_KEY_MGMT_DPP && sm->dpp_z) {
		z = wpabuf_head(sm->dpp_z);
		z_len = wpabuf_len(sm->dpp_z);
	}
#endif /* CONFIG_DPP2 */

	return wpa_pmk_to_ptk(pmk, pmk_len, "Pairwise key expansion",
			      sm->wpa_auth->addr, sm->addr, sm->ANonce, snonce,
			      ptk, sm->wpa_key_mgmt, sm->pairwise, z, z_len);
}