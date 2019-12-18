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
struct TYPE_2__ {int /*<<< orphan*/  domain_name_len; scalar_t__ domain_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANQP_DOMAIN_NAME ; 
 scalar_t__ anqp_add_override (struct hostapd_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void anqp_add_domain_name(struct hostapd_data *hapd, struct wpabuf *buf)
{
	if (anqp_add_override(hapd, buf, ANQP_DOMAIN_NAME))
		return;

	if (hapd->conf->domain_name) {
		wpabuf_put_le16(buf, ANQP_DOMAIN_NAME);
		wpabuf_put_le16(buf, hapd->conf->domain_name_len);
		wpabuf_put_data(buf, hapd->conf->domain_name,
				hapd->conf->domain_name_len);
	}
}