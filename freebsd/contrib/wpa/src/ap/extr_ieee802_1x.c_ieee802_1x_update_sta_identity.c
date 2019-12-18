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
struct sta_info {int /*<<< orphan*/  addr; struct eapol_state_machine* eapol_sm; } ;
struct radius_msg {int dummy; } ;
struct hostapd_data {int dummy; } ;
struct eapol_state_machine {size_t identity_len; int /*<<< orphan*/ * identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAPD_LEVEL_DEBUG ; 
 int /*<<< orphan*/  HOSTAPD_MODULE_IEEE8021X ; 
 int /*<<< orphan*/  RADIUS_ATTR_USER_NAME ; 
 scalar_t__ dup_binstr (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  hostapd_logger (struct hostapd_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ radius_msg_get_attr_ptr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee802_1x_update_sta_identity(struct hostapd_data *hapd,
					   struct sta_info *sta,
					   struct radius_msg *msg)
{
	u8 *buf, *identity;
	size_t len;
	struct eapol_state_machine *sm = sta->eapol_sm;

	if (sm == NULL)
		return;

	if (radius_msg_get_attr_ptr(msg, RADIUS_ATTR_USER_NAME, &buf, &len,
				    NULL) < 0)
		return;

	identity = (u8 *) dup_binstr(buf, len);
	if (identity == NULL)
		return;

	hostapd_logger(hapd, sta->addr, HOSTAPD_MODULE_IEEE8021X,
		       HOSTAPD_LEVEL_DEBUG, "old identity '%s' updated with "
		       "User-Name from Access-Accept '%s'",
		       sm->identity ? (char *) sm->identity : "N/A",
		       (char *) identity);

	os_free(sm->identity);
	sm->identity = identity;
	sm->identity_len = len;
}