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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_state_machine {int /*<<< orphan*/  wpa_auth; } ;
struct wpa_channel_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_WARNING ; 
 int ocv_insert_oci_kde (struct wpa_channel_info*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  wpa_auth_uses_ocv (struct wpa_state_machine*) ; 
 scalar_t__ wpa_channel_info (int /*<<< orphan*/ ,struct wpa_channel_info*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ocv_oci_add(struct wpa_state_machine *sm, u8 **argpos)
{
#ifdef CONFIG_OCV
	struct wpa_channel_info ci;

	if (!wpa_auth_uses_ocv(sm))
		return 0;

	if (wpa_channel_info(sm->wpa_auth, &ci) != 0) {
		wpa_printf(MSG_WARNING,
			   "Failed to get channel info for OCI element");
		return -1;
	}

	return ocv_insert_oci_kde(&ci, argpos);
#else /* CONFIG_OCV */
	return 0;
#endif /* CONFIG_OCV */
}