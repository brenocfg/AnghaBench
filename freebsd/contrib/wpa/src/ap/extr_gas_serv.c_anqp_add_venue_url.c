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
struct wpabuf {int dummy; } ;
struct hostapd_venue_url {scalar_t__ url_len; int /*<<< orphan*/  url; scalar_t__ venue_number; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {unsigned int venue_url_count; struct hostapd_venue_url* venue_url; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANQP_VENUE_URL ; 
 scalar_t__ anqp_add_override (struct hostapd_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gas_anqp_add_element (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gas_anqp_set_element_len (struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

__attribute__((used)) static void anqp_add_venue_url(struct hostapd_data *hapd, struct wpabuf *buf)
{
	if (anqp_add_override(hapd, buf, ANQP_VENUE_URL))
		return;

	if (hapd->conf->venue_url) {
		u8 *len;
		unsigned int i;

		len = gas_anqp_add_element(buf, ANQP_VENUE_URL);
		for (i = 0; i < hapd->conf->venue_url_count; i++) {
			struct hostapd_venue_url *url;

			url = &hapd->conf->venue_url[i];
			wpabuf_put_u8(buf, 1 + url->url_len);
			wpabuf_put_u8(buf, url->venue_number);
			wpabuf_put_data(buf, url->url, url->url_len);
		}
		gas_anqp_set_element_len(buf, len);
	}
}