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
struct wpa_cred {int /*<<< orphan*/  required_roaming_consortium_len; int /*<<< orphan*/  required_roaming_consortium; } ;
struct wpa_bss {TYPE_1__* anqp; } ;
struct TYPE_2__ {int /*<<< orphan*/ * roaming_consortium; } ;

/* Variables and functions */
 int /*<<< orphan*/  WLAN_EID_ROAMING_CONSORTIUM ; 
 int /*<<< orphan*/  roaming_consortium_match (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpa_bss_get_ie (struct wpa_bss*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cred_no_required_oi_match(struct wpa_cred *cred, struct wpa_bss *bss)
{
	const u8 *ie;

	if (cred->required_roaming_consortium_len == 0)
		return 0;

	ie = wpa_bss_get_ie(bss, WLAN_EID_ROAMING_CONSORTIUM);

	if (ie == NULL &&
	    (bss->anqp == NULL || bss->anqp->roaming_consortium == NULL))
		return 1;

	return !roaming_consortium_match(ie,
					 bss->anqp ?
					 bss->anqp->roaming_consortium : NULL,
					 cred->required_roaming_consortium,
					 cred->required_roaming_consortium_len);
}