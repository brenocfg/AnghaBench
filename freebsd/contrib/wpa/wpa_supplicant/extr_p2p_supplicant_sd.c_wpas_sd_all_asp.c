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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {TYPE_1__* global; } ;
typedef  int /*<<< orphan*/  q ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 scalar_t__ p2p_get_p2ps_adv_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_sd_req_asp (struct wpa_supplicant*,struct wpabuf*,int,int const*,int) ; 

__attribute__((used)) static void wpas_sd_all_asp(struct wpa_supplicant *wpa_s,
			    struct wpabuf *resp, u8 srv_trans_id)
{
	/* Query data to add all P2PS advertisements:
	 *  - Service name length: 1
	 *  - Service name: '*'
	 *  - Service Information Request Length: 0
	 */
	const u8 q[] = { 1, (const u8) '*', 0 };

	if (p2p_get_p2ps_adv_list(wpa_s->global->p2p))
		wpas_sd_req_asp(wpa_s, resp, srv_trans_id, q, sizeof(q));
}