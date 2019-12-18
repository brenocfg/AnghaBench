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
struct hostapd_lang_string {int name_len; int /*<<< orphan*/  name; int /*<<< orphan*/  lang; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int venue_group; int venue_type; unsigned int venue_name_count; struct hostapd_lang_string* venue_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANQP_VENUE_NAME ; 
 scalar_t__ anqp_add_override (struct hostapd_data*,struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gas_anqp_add_element (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gas_anqp_set_element_len (struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static void anqp_add_venue_name(struct hostapd_data *hapd, struct wpabuf *buf)
{
	if (anqp_add_override(hapd, buf, ANQP_VENUE_NAME))
		return;

	if (hapd->conf->venue_name) {
		u8 *len;
		unsigned int i;
		len = gas_anqp_add_element(buf, ANQP_VENUE_NAME);
		wpabuf_put_u8(buf, hapd->conf->venue_group);
		wpabuf_put_u8(buf, hapd->conf->venue_type);
		for (i = 0; i < hapd->conf->venue_name_count; i++) {
			struct hostapd_lang_string *vn;
			vn = &hapd->conf->venue_name[i];
			wpabuf_put_u8(buf, 3 + vn->name_len);
			wpabuf_put_data(buf, vn->lang, 3);
			wpabuf_put_data(buf, vn->name, vn->name_len);
		}
		gas_anqp_set_element_len(buf, len);
	}
}