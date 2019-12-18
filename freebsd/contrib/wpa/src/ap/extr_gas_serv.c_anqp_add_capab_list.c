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
typedef  int u16 ;
struct wpabuf {int dummy; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ venue_url; int /*<<< orphan*/  fils_realms; scalar_t__ domain_name; scalar_t__ anqp_3gpp_cell_net; scalar_t__ nai_realm_data; scalar_t__ ipaddr_type_configured; scalar_t__ roaming_consortium; scalar_t__ network_auth_type; scalar_t__ venue_name; } ;

/* Variables and functions */
 int ANQP_3GPP_CELLULAR_NETWORK ; 
 int ANQP_ADVICE_OF_CHARGE ; 
 int ANQP_AP_CIVIC_LOCATION ; 
 int ANQP_AP_GEOSPATIAL_LOCATION ; 
 int ANQP_AP_LOCATION_PUBLIC_URI ; 
 int ANQP_CAG ; 
 int ANQP_CAPABILITY_LIST ; 
 int ANQP_DOMAIN_NAME ; 
 int ANQP_EMERGENCY_ALERT_URI ; 
 int ANQP_EMERGENCY_CALL_NUMBER ; 
 int ANQP_EMERGENCY_NAI ; 
 int ANQP_FILS_REALM_INFO ; 
 int ANQP_IP_ADDR_TYPE_AVAILABILITY ; 
 int ANQP_LOCAL_CONTENT ; 
 int ANQP_NAI_REALM ; 
 int ANQP_NEIGHBOR_REPORT ; 
 int ANQP_NETWORK_AUTH_TYPE ; 
 int ANQP_ROAMING_CONSORTIUM ; 
 int ANQP_TDLS_CAPABILITY ; 
 int ANQP_VENUE_NAME ; 
 int ANQP_VENUE_URL ; 
 int /*<<< orphan*/  anqp_add_hs_capab_list (struct hostapd_data*,struct wpabuf*) ; 
 scalar_t__ anqp_add_override (struct hostapd_data*,struct wpabuf*,int) ; 
 int /*<<< orphan*/  dl_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gas_anqp_add_element (struct wpabuf*,int) ; 
 int /*<<< orphan*/  gas_anqp_set_element_len (struct wpabuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_anqp_elem (struct hostapd_data*,int) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int) ; 

__attribute__((used)) static void anqp_add_capab_list(struct hostapd_data *hapd,
				struct wpabuf *buf)
{
	u8 *len;
	u16 id;

	if (anqp_add_override(hapd, buf, ANQP_CAPABILITY_LIST))
		return;

	len = gas_anqp_add_element(buf, ANQP_CAPABILITY_LIST);
	wpabuf_put_le16(buf, ANQP_CAPABILITY_LIST);
	if (hapd->conf->venue_name || get_anqp_elem(hapd, ANQP_VENUE_NAME))
		wpabuf_put_le16(buf, ANQP_VENUE_NAME);
	if (get_anqp_elem(hapd, ANQP_EMERGENCY_CALL_NUMBER))
		wpabuf_put_le16(buf, ANQP_EMERGENCY_CALL_NUMBER);
	if (hapd->conf->network_auth_type ||
	    get_anqp_elem(hapd, ANQP_NETWORK_AUTH_TYPE))
		wpabuf_put_le16(buf, ANQP_NETWORK_AUTH_TYPE);
	if (hapd->conf->roaming_consortium ||
	    get_anqp_elem(hapd, ANQP_ROAMING_CONSORTIUM))
		wpabuf_put_le16(buf, ANQP_ROAMING_CONSORTIUM);
	if (hapd->conf->ipaddr_type_configured ||
	    get_anqp_elem(hapd, ANQP_IP_ADDR_TYPE_AVAILABILITY))
		wpabuf_put_le16(buf, ANQP_IP_ADDR_TYPE_AVAILABILITY);
	if (hapd->conf->nai_realm_data ||
	    get_anqp_elem(hapd, ANQP_NAI_REALM))
		wpabuf_put_le16(buf, ANQP_NAI_REALM);
	if (hapd->conf->anqp_3gpp_cell_net ||
	    get_anqp_elem(hapd, ANQP_3GPP_CELLULAR_NETWORK))
		wpabuf_put_le16(buf, ANQP_3GPP_CELLULAR_NETWORK);
	if (get_anqp_elem(hapd, ANQP_AP_GEOSPATIAL_LOCATION))
		wpabuf_put_le16(buf, ANQP_AP_GEOSPATIAL_LOCATION);
	if (get_anqp_elem(hapd, ANQP_AP_CIVIC_LOCATION))
		wpabuf_put_le16(buf, ANQP_AP_CIVIC_LOCATION);
	if (get_anqp_elem(hapd, ANQP_AP_LOCATION_PUBLIC_URI))
		wpabuf_put_le16(buf, ANQP_AP_LOCATION_PUBLIC_URI);
	if (hapd->conf->domain_name || get_anqp_elem(hapd, ANQP_DOMAIN_NAME))
		wpabuf_put_le16(buf, ANQP_DOMAIN_NAME);
	if (get_anqp_elem(hapd, ANQP_EMERGENCY_ALERT_URI))
		wpabuf_put_le16(buf, ANQP_EMERGENCY_ALERT_URI);
	if (get_anqp_elem(hapd, ANQP_TDLS_CAPABILITY))
		wpabuf_put_le16(buf, ANQP_TDLS_CAPABILITY);
	if (get_anqp_elem(hapd, ANQP_EMERGENCY_NAI))
		wpabuf_put_le16(buf, ANQP_EMERGENCY_NAI);
	if (get_anqp_elem(hapd, ANQP_NEIGHBOR_REPORT))
		wpabuf_put_le16(buf, ANQP_NEIGHBOR_REPORT);
#ifdef CONFIG_FILS
	if (!dl_list_empty(&hapd->conf->fils_realms) ||
	    get_anqp_elem(hapd, ANQP_FILS_REALM_INFO))
		wpabuf_put_le16(buf, ANQP_FILS_REALM_INFO);
#endif /* CONFIG_FILS */
	if (get_anqp_elem(hapd, ANQP_CAG))
		wpabuf_put_le16(buf, ANQP_CAG);
	if (hapd->conf->venue_url || get_anqp_elem(hapd, ANQP_VENUE_URL))
		wpabuf_put_le16(buf, ANQP_VENUE_URL);
	if (get_anqp_elem(hapd, ANQP_ADVICE_OF_CHARGE))
		wpabuf_put_le16(buf, ANQP_ADVICE_OF_CHARGE);
	if (get_anqp_elem(hapd, ANQP_LOCAL_CONTENT))
		wpabuf_put_le16(buf, ANQP_LOCAL_CONTENT);
	for (id = 280; id < 300; id++) {
		if (get_anqp_elem(hapd, id))
			wpabuf_put_le16(buf, id);
	}
#ifdef CONFIG_HS20
	anqp_add_hs_capab_list(hapd, buf);
#endif /* CONFIG_HS20 */
	gas_anqp_set_element_len(buf, len);
}