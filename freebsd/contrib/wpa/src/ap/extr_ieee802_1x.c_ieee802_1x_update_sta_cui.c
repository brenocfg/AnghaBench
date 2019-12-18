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
struct wpabuf {int dummy; } ;
struct sta_info {struct eapol_state_machine* eapol_sm; } ;
struct radius_msg {int dummy; } ;
struct hostapd_data {int dummy; } ;
struct eapol_state_machine {struct wpabuf* radius_cui; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIUS_ATTR_CHARGEABLE_USER_IDENTITY ; 
 scalar_t__ radius_msg_get_attr_ptr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 struct wpabuf* wpabuf_alloc_copy (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static void ieee802_1x_update_sta_cui(struct hostapd_data *hapd,
				      struct sta_info *sta,
				      struct radius_msg *msg)
{
	struct eapol_state_machine *sm = sta->eapol_sm;
	struct wpabuf *cui;
	u8 *buf;
	size_t len;

	if (sm == NULL)
		return;

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_CHARGEABLE_USER_IDENTITY,
				    &buf, &len, NULL) < 0)
		return;

	cui = wpabuf_alloc_copy(buf, len);
	if (cui == NULL)
		return;

	wpabuf_free(sm->radius_cui);
	sm->radius_cui = cui;
}