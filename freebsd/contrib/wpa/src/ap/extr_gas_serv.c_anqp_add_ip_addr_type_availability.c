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
struct TYPE_2__ {int /*<<< orphan*/  ipaddr_type_availability; scalar_t__ ipaddr_type_configured; } ;

/* Variables and functions */
 int ANQP_IP_ADDR_TYPE_AVAILABILITY ; 
 scalar_t__ anqp_add_override (struct hostapd_data*,struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void anqp_add_ip_addr_type_availability(struct hostapd_data *hapd,
					       struct wpabuf *buf)
{
	if (anqp_add_override(hapd, buf, ANQP_IP_ADDR_TYPE_AVAILABILITY))
		return;

	if (hapd->conf->ipaddr_type_configured) {
		wpabuf_put_le16(buf, ANQP_IP_ADDR_TYPE_AVAILABILITY);
		wpabuf_put_le16(buf, 1);
		wpabuf_put_u8(buf, hapd->conf->ipaddr_type_availability);
	}
}