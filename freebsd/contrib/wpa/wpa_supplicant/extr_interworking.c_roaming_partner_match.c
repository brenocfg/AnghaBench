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
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int dummy; } ;
struct roaming_partner {int /*<<< orphan*/  exact_match; int /*<<< orphan*/  fqdn; int /*<<< orphan*/  country; int /*<<< orphan*/  priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  domain_name_list_contains (struct wpabuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 

__attribute__((used)) static int roaming_partner_match(struct wpa_supplicant *wpa_s,
				 struct roaming_partner *partner,
				 struct wpabuf *domain_names)
{
	wpa_printf(MSG_DEBUG, "Interworking: Comparing roaming_partner info fqdn='%s' exact_match=%d priority=%u country='%s'",
		   partner->fqdn, partner->exact_match, partner->priority,
		   partner->country);
	wpa_hexdump_ascii(MSG_DEBUG, "Interworking: Domain names",
			  wpabuf_head(domain_names),
			  wpabuf_len(domain_names));
	if (!domain_name_list_contains(domain_names, partner->fqdn,
				       partner->exact_match))
		return 0;
	/* TODO: match Country */
	return 1;
}