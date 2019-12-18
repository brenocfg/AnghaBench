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
typedef  char const u8 ;
struct eap_eke_session {scalar_t__ encr; scalar_t__ mac; char const* ke; char const* ki; int /*<<< orphan*/  prf_len; int /*<<< orphan*/  shared_secret; int /*<<< orphan*/  prf; } ;

/* Variables and functions */
 scalar_t__ EAP_EKE_ENCR_AES128_CBC ; 
 int EAP_EKE_MAX_KE_LEN ; 
 int EAP_EKE_MAX_KI_LEN ; 
 scalar_t__ EAP_EKE_PRF_HMAC_SHA1 ; 
 scalar_t__ EAP_EKE_PRF_HMAC_SHA2_256 ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_eke_prfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t,char const*,size_t) ; 
 int /*<<< orphan*/  os_free (char const*) ; 
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char const*,char const*,size_t) ; 
 size_t os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,char const*,size_t) ; 

int eap_eke_derive_ke_ki(struct eap_eke_session *sess,
			 const u8 *id_s, size_t id_s_len,
			 const u8 *id_p, size_t id_p_len)
{
	u8 buf[EAP_EKE_MAX_KE_LEN + EAP_EKE_MAX_KI_LEN];
	size_t ke_len, ki_len;
	u8 *data;
	size_t data_len;
	const char *label = "EAP-EKE Keys";
	size_t label_len;

	/*
	 * Ke | Ki = prf+(SharedSecret, "EAP-EKE Keys" | ID_S | ID_P)
	 * Ke = encryption key
	 * Ki = integrity protection key
	 * Length of each key depends on the selected algorithms.
	 */

	if (sess->encr == EAP_EKE_ENCR_AES128_CBC)
		ke_len = 16;
	else
		return -1;

	if (sess->mac == EAP_EKE_PRF_HMAC_SHA1)
		ki_len = 20;
	else if (sess->mac == EAP_EKE_PRF_HMAC_SHA2_256)
		ki_len = 32;
	else
		return -1;

	label_len = os_strlen(label);
	data_len = label_len + id_s_len + id_p_len;
	data = os_malloc(data_len);
	if (data == NULL)
		return -1;
	os_memcpy(data, label, label_len);
	os_memcpy(data + label_len, id_s, id_s_len);
	os_memcpy(data + label_len + id_s_len, id_p, id_p_len);
	if (eap_eke_prfplus(sess->prf, sess->shared_secret, sess->prf_len,
			    data, data_len, buf, ke_len + ki_len) < 0) {
		os_free(data);
		return -1;
	}

	os_memcpy(sess->ke, buf, ke_len);
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: Ke", sess->ke, ke_len);
	os_memcpy(sess->ki, buf + ke_len, ki_len);
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: Ki", sess->ki, ki_len);

	os_free(data);
	return 0;
}