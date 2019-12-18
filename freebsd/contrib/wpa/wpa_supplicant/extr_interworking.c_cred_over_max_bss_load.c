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
struct wpa_supplicant {int dummy; } ;
struct wpa_cred {int const max_bss_load; } ;
struct wpa_bss {TYPE_1__* anqp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * domain_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_BSS_LOAD ; 
 int interworking_home_sp_cred (struct wpa_supplicant*,struct wpa_cred*,int /*<<< orphan*/ *) ; 
 int* wpa_bss_get_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cred_over_max_bss_load(struct wpa_supplicant *wpa_s,
				  struct wpa_cred *cred, struct wpa_bss *bss)
{
	const u8 *ie;
	int res;

	if (!cred->max_bss_load)
		return 0; /* No BSS Load constraint specified */

	ie = wpa_bss_get_ie(bss, WLAN_EID_BSS_LOAD);
	if (ie == NULL || ie[1] < 3)
		return 0; /* No BSS Load advertised */

	res = interworking_home_sp_cred(wpa_s, cred, bss->anqp ?
					bss->anqp->domain_name : NULL);
	if (res <= 0)
		return 0; /* Not a home network */

	return ie[4] > cred->max_bss_load;
}