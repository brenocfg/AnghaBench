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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  key_buf ;

/* Variables and functions */
 int EAP_EMSK_LEN ; 
 int EAP_MSK_LEN ; 
 int /*<<< orphan*/  EAP_SAKE_RAND_LEN ; 
 int EAP_SAKE_ROOT_SECRET_LEN ; 
 int EAP_SAKE_SMS_LEN ; 
 int EAP_SAKE_TEK_AUTH_LEN ; 
 int EAP_SAKE_TEK_CIPHER_LEN ; 
 int EAP_SAKE_TEK_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ eap_sake_kdf (int /*<<< orphan*/  const*,int,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int eap_sake_derive_keys(const u8 *root_secret_a, const u8 *root_secret_b,
			 const u8 *rand_s, const u8 *rand_p, u8 *tek, u8 *msk,
			 u8 *emsk)
{
	u8 sms_a[EAP_SAKE_SMS_LEN];
	u8 sms_b[EAP_SAKE_SMS_LEN];
	u8 key_buf[EAP_MSK_LEN + EAP_EMSK_LEN];

	wpa_printf(MSG_DEBUG, "EAP-SAKE: Deriving keys");

	wpa_hexdump_key(MSG_DEBUG, "EAP-SAKE: Root-Secret-A",
			root_secret_a, EAP_SAKE_ROOT_SECRET_LEN);
	if (eap_sake_kdf(root_secret_a, EAP_SAKE_ROOT_SECRET_LEN,
			 "SAKE Master Secret A",
			 rand_p, EAP_SAKE_RAND_LEN, rand_s, EAP_SAKE_RAND_LEN,
			 sms_a, EAP_SAKE_SMS_LEN) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-SAKE: SMS-A", sms_a, EAP_SAKE_SMS_LEN);
	if (eap_sake_kdf(sms_a, EAP_SAKE_SMS_LEN, "Transient EAP Key",
			 rand_s, EAP_SAKE_RAND_LEN, rand_p, EAP_SAKE_RAND_LEN,
			 tek, EAP_SAKE_TEK_LEN) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-SAKE: TEK-Auth",
			tek, EAP_SAKE_TEK_AUTH_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-SAKE: TEK-Cipher",
			tek + EAP_SAKE_TEK_AUTH_LEN, EAP_SAKE_TEK_CIPHER_LEN);

	wpa_hexdump_key(MSG_DEBUG, "EAP-SAKE: Root-Secret-B",
			root_secret_b, EAP_SAKE_ROOT_SECRET_LEN);
	if (eap_sake_kdf(root_secret_b, EAP_SAKE_ROOT_SECRET_LEN,
			 "SAKE Master Secret B",
			 rand_p, EAP_SAKE_RAND_LEN, rand_s, EAP_SAKE_RAND_LEN,
			 sms_b, EAP_SAKE_SMS_LEN) < 0)
		return -1;
	wpa_hexdump_key(MSG_DEBUG, "EAP-SAKE: SMS-B", sms_b, EAP_SAKE_SMS_LEN);
	if (eap_sake_kdf(sms_b, EAP_SAKE_SMS_LEN, "Master Session Key",
			 rand_s, EAP_SAKE_RAND_LEN, rand_p, EAP_SAKE_RAND_LEN,
			 key_buf, sizeof(key_buf)) < 0)
		return -1;
	os_memcpy(msk, key_buf, EAP_MSK_LEN);
	os_memcpy(emsk, key_buf + EAP_MSK_LEN, EAP_EMSK_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-SAKE: MSK", msk, EAP_MSK_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-SAKE: EMSK", emsk, EAP_EMSK_LEN);
	return 0;
}