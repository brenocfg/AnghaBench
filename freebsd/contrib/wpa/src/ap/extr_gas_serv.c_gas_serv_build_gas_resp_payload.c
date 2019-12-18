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
typedef  unsigned int u16 ;
struct wpabuf {int dummy; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {int /*<<< orphan*/  fils_realms; } ;

/* Variables and functions */
 unsigned int const ANQP_AP_CIVIC_LOCATION ; 
 unsigned int const ANQP_AP_GEOSPATIAL_LOCATION ; 
 unsigned int const ANQP_AP_LOCATION_PUBLIC_URI ; 
 unsigned int const ANQP_EMERGENCY_ALERT_URI ; 
 unsigned int const ANQP_EMERGENCY_CALL_NUMBER ; 
 unsigned int const ANQP_EMERGENCY_NAI ; 
 unsigned int ANQP_FILS_REALM_INFO ; 
 unsigned int ANQP_REQ_3GPP_CELLULAR_NETWORK ; 
 unsigned int ANQP_REQ_AP_CIVIC_LOCATION ; 
 unsigned int ANQP_REQ_AP_GEOSPATIAL_LOCATION ; 
 unsigned int ANQP_REQ_AP_LOCATION_PUBLIC_URI ; 
 unsigned int ANQP_REQ_CAPABILITY_LIST ; 
 unsigned int ANQP_REQ_CONNECTION_CAPABILITY ; 
 unsigned int ANQP_REQ_DOMAIN_NAME ; 
 unsigned int ANQP_REQ_EMERGENCY_ALERT_URI ; 
 unsigned int ANQP_REQ_EMERGENCY_CALL_NUMBER ; 
 unsigned int ANQP_REQ_EMERGENCY_NAI ; 
 unsigned int ANQP_REQ_HS_CAPABILITY_LIST ; 
 unsigned int ANQP_REQ_ICON_REQUEST ; 
 unsigned int ANQP_REQ_IP_ADDR_TYPE_AVAILABILITY ; 
 unsigned int ANQP_REQ_MBO_CELL_DATA_CONN_PREF ; 
 unsigned int ANQP_REQ_NAI_HOME_REALM ; 
 unsigned int ANQP_REQ_NAI_REALM ; 
 unsigned int ANQP_REQ_NETWORK_AUTH_TYPE ; 
 unsigned int ANQP_REQ_OPERATING_CLASS ; 
 unsigned int ANQP_REQ_OPERATOR_FRIENDLY_NAME ; 
 unsigned int ANQP_REQ_OPERATOR_ICON_METADATA ; 
 unsigned int ANQP_REQ_OSU_PROVIDERS_LIST ; 
 unsigned int ANQP_REQ_OSU_PROVIDERS_NAI_LIST ; 
 unsigned int ANQP_REQ_ROAMING_CONSORTIUM ; 
 unsigned int ANQP_REQ_TDLS_CAPABILITY ; 
 unsigned int ANQP_REQ_VENUE_NAME ; 
 unsigned int ANQP_REQ_WAN_METRICS ; 
 unsigned int const ANQP_TDLS_CAPABILITY ; 
 unsigned int const ANQP_VENUE_URL ; 
 int /*<<< orphan*/  anqp_add_3gpp_cellular_network (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_capab_list (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_connection_capability (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_domain_name (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_elem (struct hostapd_data*,struct wpabuf*,unsigned int const) ; 
 int /*<<< orphan*/  anqp_add_fils_realm_info (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_hs_capab_list (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_icon_binary_file (struct hostapd_data*,struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  anqp_add_ip_addr_type_availability (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_mbo_cell_data_conn_pref (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_nai_realm (struct hostapd_data*,struct wpabuf*,int /*<<< orphan*/  const*,size_t,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  anqp_add_network_auth_type (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_operating_class (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_operator_friendly_name (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_operator_icon_metadata (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_osu_providers_list (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_osu_providers_nai_list (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_roaming_consortium (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_venue_name (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_venue_url (struct hostapd_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  anqp_add_wan_metrics (struct hostapd_data*,struct wpabuf*) ; 
 scalar_t__ anqp_get_required_len (struct hostapd_data*,unsigned int const*,unsigned int) ; 
 int dl_list_len (int /*<<< orphan*/ *) ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 

__attribute__((used)) static struct wpabuf *
gas_serv_build_gas_resp_payload(struct hostapd_data *hapd,
				unsigned int request,
				const u8 *home_realm, size_t home_realm_len,
				const u8 *icon_name, size_t icon_name_len,
				const u16 *extra_req,
				unsigned int num_extra_req)
{
	struct wpabuf *buf;
	size_t len;
	unsigned int i;

	len = 1400;
	if (request & (ANQP_REQ_NAI_REALM | ANQP_REQ_NAI_HOME_REALM))
		len += 1000;
	if (request & ANQP_REQ_ICON_REQUEST)
		len += 65536;
#ifdef CONFIG_FILS
	if (request & ANQP_FILS_REALM_INFO)
		len += 2 * dl_list_len(&hapd->conf->fils_realms);
#endif /* CONFIG_FILS */
	len += anqp_get_required_len(hapd, extra_req, num_extra_req);

	buf = wpabuf_alloc(len);
	if (buf == NULL)
		return NULL;

	if (request & ANQP_REQ_CAPABILITY_LIST)
		anqp_add_capab_list(hapd, buf);
	if (request & ANQP_REQ_VENUE_NAME)
		anqp_add_venue_name(hapd, buf);
	if (request & ANQP_REQ_EMERGENCY_CALL_NUMBER)
		anqp_add_elem(hapd, buf, ANQP_EMERGENCY_CALL_NUMBER);
	if (request & ANQP_REQ_NETWORK_AUTH_TYPE)
		anqp_add_network_auth_type(hapd, buf);
	if (request & ANQP_REQ_ROAMING_CONSORTIUM)
		anqp_add_roaming_consortium(hapd, buf);
	if (request & ANQP_REQ_IP_ADDR_TYPE_AVAILABILITY)
		anqp_add_ip_addr_type_availability(hapd, buf);
	if (request & (ANQP_REQ_NAI_REALM | ANQP_REQ_NAI_HOME_REALM))
		anqp_add_nai_realm(hapd, buf, home_realm, home_realm_len,
				   request & ANQP_REQ_NAI_REALM,
				   request & ANQP_REQ_NAI_HOME_REALM);
	if (request & ANQP_REQ_3GPP_CELLULAR_NETWORK)
		anqp_add_3gpp_cellular_network(hapd, buf);
	if (request & ANQP_REQ_AP_GEOSPATIAL_LOCATION)
		anqp_add_elem(hapd, buf, ANQP_AP_GEOSPATIAL_LOCATION);
	if (request & ANQP_REQ_AP_CIVIC_LOCATION)
		anqp_add_elem(hapd, buf, ANQP_AP_CIVIC_LOCATION);
	if (request & ANQP_REQ_AP_LOCATION_PUBLIC_URI)
		anqp_add_elem(hapd, buf, ANQP_AP_LOCATION_PUBLIC_URI);
	if (request & ANQP_REQ_DOMAIN_NAME)
		anqp_add_domain_name(hapd, buf);
	if (request & ANQP_REQ_EMERGENCY_ALERT_URI)
		anqp_add_elem(hapd, buf, ANQP_EMERGENCY_ALERT_URI);
	if (request & ANQP_REQ_TDLS_CAPABILITY)
		anqp_add_elem(hapd, buf, ANQP_TDLS_CAPABILITY);
	if (request & ANQP_REQ_EMERGENCY_NAI)
		anqp_add_elem(hapd, buf, ANQP_EMERGENCY_NAI);

	for (i = 0; i < num_extra_req; i++) {
#ifdef CONFIG_FILS
		if (extra_req[i] == ANQP_FILS_REALM_INFO) {
			anqp_add_fils_realm_info(hapd, buf);
			continue;
		}
#endif /* CONFIG_FILS */
		if (extra_req[i] == ANQP_VENUE_URL) {
			anqp_add_venue_url(hapd, buf);
			continue;
		}
		anqp_add_elem(hapd, buf, extra_req[i]);
	}

#ifdef CONFIG_HS20
	if (request & ANQP_REQ_HS_CAPABILITY_LIST)
		anqp_add_hs_capab_list(hapd, buf);
	if (request & ANQP_REQ_OPERATOR_FRIENDLY_NAME)
		anqp_add_operator_friendly_name(hapd, buf);
	if (request & ANQP_REQ_WAN_METRICS)
		anqp_add_wan_metrics(hapd, buf);
	if (request & ANQP_REQ_CONNECTION_CAPABILITY)
		anqp_add_connection_capability(hapd, buf);
	if (request & ANQP_REQ_OPERATING_CLASS)
		anqp_add_operating_class(hapd, buf);
	if (request & ANQP_REQ_OSU_PROVIDERS_LIST)
		anqp_add_osu_providers_list(hapd, buf);
	if (request & ANQP_REQ_ICON_REQUEST)
		anqp_add_icon_binary_file(hapd, buf, icon_name, icon_name_len);
	if (request & ANQP_REQ_OPERATOR_ICON_METADATA)
		anqp_add_operator_icon_metadata(hapd, buf);
	if (request & ANQP_REQ_OSU_PROVIDERS_NAI_LIST)
		anqp_add_osu_providers_nai_list(hapd, buf);
#endif /* CONFIG_HS20 */

#ifdef CONFIG_MBO
	if (request & ANQP_REQ_MBO_CELL_DATA_CONN_PREF)
		anqp_add_mbo_cell_data_conn_pref(hapd, buf);
#endif /* CONFIG_MBO */

	return buf;
}