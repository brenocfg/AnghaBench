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

/* Variables and functions */
 int eap_server_aka_prime_register () ; 
 int eap_server_aka_register () ; 
 int eap_server_eke_register () ; 
 int eap_server_fast_register () ; 
 int eap_server_gpsk_register () ; 
 int eap_server_gtc_register () ; 
 int eap_server_identity_register () ; 
 int eap_server_ikev2_register () ; 
 int eap_server_md5_register () ; 
 int eap_server_mschapv2_register () ; 
 int eap_server_pax_register () ; 
 int eap_server_peap_register () ; 
 int eap_server_psk_register () ; 
 int eap_server_pwd_register () ; 
 int eap_server_sake_register () ; 
 int eap_server_sim_register () ; 
 int eap_server_teap_register () ; 
 int eap_server_tls_register () ; 
 int eap_server_tlv_register () ; 
 int eap_server_tnc_register () ; 
 int eap_server_ttls_register () ; 
 int eap_server_unauth_tls_register () ; 
 int eap_server_vendor_test_register () ; 
 int eap_server_wfa_unauth_tls_register () ; 
 int eap_server_wsc_register () ; 

int eap_server_register_methods(void)
{
	int ret = 0;

#ifdef EAP_SERVER_IDENTITY
	if (ret == 0)
		ret = eap_server_identity_register();
#endif /* EAP_SERVER_IDENTITY */

#ifdef EAP_SERVER_MD5
	if (ret == 0)
		ret = eap_server_md5_register();
#endif /* EAP_SERVER_MD5 */

#ifdef EAP_SERVER_TLS
	if (ret == 0)
		ret = eap_server_tls_register();
#endif /* EAP_SERVER_TLS */

#ifdef EAP_SERVER_UNAUTH_TLS
	if (ret == 0)
		ret = eap_server_unauth_tls_register();
#endif /* EAP_SERVER_TLS */

#ifdef EAP_SERVER_TLS
#ifdef CONFIG_HS20
	if (ret == 0)
		ret = eap_server_wfa_unauth_tls_register();
#endif /* CONFIG_HS20 */
#endif /* EAP_SERVER_TLS */

#ifdef EAP_SERVER_MSCHAPV2
	if (ret == 0)
		ret = eap_server_mschapv2_register();
#endif /* EAP_SERVER_MSCHAPV2 */

#ifdef EAP_SERVER_PEAP
	if (ret == 0)
		ret = eap_server_peap_register();
#endif /* EAP_SERVER_PEAP */

#ifdef EAP_SERVER_TLV
	if (ret == 0)
		ret = eap_server_tlv_register();
#endif /* EAP_SERVER_TLV */

#ifdef EAP_SERVER_GTC
	if (ret == 0)
		ret = eap_server_gtc_register();
#endif /* EAP_SERVER_GTC */

#ifdef EAP_SERVER_TTLS
	if (ret == 0)
		ret = eap_server_ttls_register();
#endif /* EAP_SERVER_TTLS */

#ifdef EAP_SERVER_SIM
	if (ret == 0)
		ret = eap_server_sim_register();
#endif /* EAP_SERVER_SIM */

#ifdef EAP_SERVER_AKA
	if (ret == 0)
		ret = eap_server_aka_register();
#endif /* EAP_SERVER_AKA */

#ifdef EAP_SERVER_AKA_PRIME
	if (ret == 0)
		ret = eap_server_aka_prime_register();
#endif /* EAP_SERVER_AKA_PRIME */

#ifdef EAP_SERVER_PAX
	if (ret == 0)
		ret = eap_server_pax_register();
#endif /* EAP_SERVER_PAX */

#ifdef EAP_SERVER_PSK
	if (ret == 0)
		ret = eap_server_psk_register();
#endif /* EAP_SERVER_PSK */

#ifdef EAP_SERVER_SAKE
	if (ret == 0)
		ret = eap_server_sake_register();
#endif /* EAP_SERVER_SAKE */

#ifdef EAP_SERVER_GPSK
	if (ret == 0)
		ret = eap_server_gpsk_register();
#endif /* EAP_SERVER_GPSK */

#ifdef EAP_SERVER_VENDOR_TEST
	if (ret == 0)
		ret = eap_server_vendor_test_register();
#endif /* EAP_SERVER_VENDOR_TEST */

#ifdef EAP_SERVER_FAST
	if (ret == 0)
		ret = eap_server_fast_register();
#endif /* EAP_SERVER_FAST */

#ifdef EAP_SERVER_TEAP
	if (ret == 0)
		ret = eap_server_teap_register();
#endif /* EAP_SERVER_TEAP */

#ifdef EAP_SERVER_WSC
	if (ret == 0)
		ret = eap_server_wsc_register();
#endif /* EAP_SERVER_WSC */

#ifdef EAP_SERVER_IKEV2
	if (ret == 0)
		ret = eap_server_ikev2_register();
#endif /* EAP_SERVER_IKEV2 */

#ifdef EAP_SERVER_TNC
	if (ret == 0)
		ret = eap_server_tnc_register();
#endif /* EAP_SERVER_TNC */

#ifdef EAP_SERVER_PWD
	if (ret == 0)
		ret = eap_server_pwd_register();
#endif /* EAP_SERVER_PWD */

#ifdef EAP_SERVER_EKE
	if (ret == 0)
		ret = eap_server_eke_register();
#endif /* EAP_SERVER_EKE */

	return ret;
}