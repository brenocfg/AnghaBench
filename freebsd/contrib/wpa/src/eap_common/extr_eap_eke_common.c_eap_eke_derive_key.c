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
typedef  int /*<<< orphan*/  u8 ;
struct eap_eke_session {size_t prf_len; int /*<<< orphan*/  prf; } ;

/* Variables and functions */
 int EAP_EKE_MAX_HASH_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_eke_prf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ eap_eke_prfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 

int eap_eke_derive_key(struct eap_eke_session *sess,
		       const u8 *password, size_t password_len,
		       const u8 *id_s, size_t id_s_len, const u8 *id_p,
		       size_t id_p_len, u8 *key)
{
	u8 zeros[EAP_EKE_MAX_HASH_LEN];
	u8 temp[EAP_EKE_MAX_HASH_LEN];
	size_t key_len = 16; /* Only AES-128-CBC is used here */
	u8 *id;

	/* temp = prf(0+, password) */
	os_memset(zeros, 0, sess->prf_len);
	if (eap_eke_prf(sess->prf, zeros, sess->prf_len,
			password, password_len, NULL, 0, temp) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: temp = prf(0+, password)",
			temp, sess->prf_len);

	/* key = prf+(temp, ID_S | ID_P) */
	id = os_malloc(id_s_len + id_p_len);
	if (id == NULL)
		return -1;
	os_memcpy(id, id_s, id_s_len);
	os_memcpy(id + id_s_len, id_p, id_p_len);
	wpa_hexdump_ascii(MSG_DEBUG, "EAP-EKE: ID_S | ID_P",
			  id, id_s_len + id_p_len);
	if (eap_eke_prfplus(sess->prf, temp, sess->prf_len,
			    id, id_s_len + id_p_len, key, key_len) < 0) {
		os_free(id);
		return -1;
	}
	os_free(id);
	wpa_hexdump_key(MSG_DEBUG, "EAP-EKE: key = prf+(temp, ID_S | ID_P)",
			key, key_len);

	return 0;
}