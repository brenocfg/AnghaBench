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
struct wpabuf {int dummy; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  network_auth_type_len; scalar_t__ network_auth_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANQP_NETWORK_AUTH_TYPE ; 
 scalar_t__ anqp_add_override (struct hostapd_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void anqp_add_network_auth_type(struct hostapd_data *hapd,
				       struct wpabuf *buf)
{
	if (anqp_add_override(hapd, buf, ANQP_NETWORK_AUTH_TYPE))
		return;

	if (hapd->conf->network_auth_type) {
		wpabuf_put_le16(buf, ANQP_NETWORK_AUTH_TYPE);
		wpabuf_put_le16(buf, hapd->conf->network_auth_type_len);
		wpabuf_put_data(buf, hapd->conf->network_auth_type,
				hapd->conf->network_auth_type_len);
	}
}