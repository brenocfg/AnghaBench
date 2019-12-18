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
struct wpa_bss_anqp {int /*<<< orphan*/  anqp_elems; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANQP_DUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  anqp_3gpp ; 
 int /*<<< orphan*/  capability_list ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  domain_name ; 
 int /*<<< orphan*/  fils_realm_info ; 
 int /*<<< orphan*/  hs20_capability_list ; 
 int /*<<< orphan*/  hs20_connection_capability ; 
 int /*<<< orphan*/  hs20_operating_class ; 
 int /*<<< orphan*/  hs20_operator_friendly_name ; 
 int /*<<< orphan*/  hs20_operator_icon_metadata ; 
 int /*<<< orphan*/  hs20_osu_providers_list ; 
 int /*<<< orphan*/  hs20_osu_providers_nai_list ; 
 int /*<<< orphan*/  hs20_wan_metrics ; 
 int /*<<< orphan*/  ip_addr_type_availability ; 
 int /*<<< orphan*/  nai_realm ; 
 int /*<<< orphan*/  network_auth_type ; 
 struct wpa_bss_anqp* os_zalloc (int) ; 
 int /*<<< orphan*/  roaming_consortium ; 
 int /*<<< orphan*/  venue_name ; 

__attribute__((used)) static struct wpa_bss_anqp * wpa_bss_anqp_clone(struct wpa_bss_anqp *anqp)
{
	struct wpa_bss_anqp *n;

	n = os_zalloc(sizeof(*n));
	if (n == NULL)
		return NULL;

#define ANQP_DUP(f) if (anqp->f) n->f = wpabuf_dup(anqp->f)
#ifdef CONFIG_INTERWORKING
	dl_list_init(&n->anqp_elems);
	ANQP_DUP(capability_list);
	ANQP_DUP(venue_name);
	ANQP_DUP(network_auth_type);
	ANQP_DUP(roaming_consortium);
	ANQP_DUP(ip_addr_type_availability);
	ANQP_DUP(nai_realm);
	ANQP_DUP(anqp_3gpp);
	ANQP_DUP(domain_name);
	ANQP_DUP(fils_realm_info);
#endif /* CONFIG_INTERWORKING */
#ifdef CONFIG_HS20
	ANQP_DUP(hs20_capability_list);
	ANQP_DUP(hs20_operator_friendly_name);
	ANQP_DUP(hs20_wan_metrics);
	ANQP_DUP(hs20_connection_capability);
	ANQP_DUP(hs20_operating_class);
	ANQP_DUP(hs20_osu_providers_list);
	ANQP_DUP(hs20_operator_icon_metadata);
	ANQP_DUP(hs20_osu_providers_nai_list);
#endif /* CONFIG_HS20 */
#undef ANQP_DUP

	return n;
}