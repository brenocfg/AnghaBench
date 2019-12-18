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
struct hostapd_nai_realm_eap {int num_auths; int eap_method; int* auth_id; int* auth_val; } ;
struct hostapd_nai_realm_data {int eap_method_count; struct hostapd_nai_realm_eap* eap_method; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static void anqp_add_nai_realm_eap(struct wpabuf *buf,
				   struct hostapd_nai_realm_data *realm)
{
	unsigned int i, j;

	wpabuf_put_u8(buf, realm->eap_method_count);

	for (i = 0; i < realm->eap_method_count; i++) {
		struct hostapd_nai_realm_eap *eap = &realm->eap_method[i];
		wpabuf_put_u8(buf, 2 + (3 * eap->num_auths));
		wpabuf_put_u8(buf, eap->eap_method);
		wpabuf_put_u8(buf, eap->num_auths);
		for (j = 0; j < eap->num_auths; j++) {
			wpabuf_put_u8(buf, eap->auth_id[j]);
			wpabuf_put_u8(buf, 1);
			wpabuf_put_u8(buf, eap->auth_val[j]);
		}
	}
}