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
struct eap_aka_data {scalar_t__ eap_method; int /*<<< orphan*/ * id_msgs; } ;

/* Variables and functions */
 size_t EAP_AKA_CHECKCODE_LEN ; 
 size_t EAP_AKA_PRIME_CHECKCODE_LEN ; 
 scalar_t__ EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SHA256_MAC_LEN ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  sha1_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpabuf_head (int /*<<< orphan*/ *) ; 
 size_t wpabuf_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int eap_aka_verify_checkcode(struct eap_aka_data *data,
				    const u8 *checkcode, size_t checkcode_len)
{
	const u8 *addr;
	size_t len;
	u8 hash[SHA256_MAC_LEN];
	size_t hash_len;

	if (checkcode == NULL)
		return -1;

	if (data->id_msgs == NULL) {
		if (checkcode_len != 0) {
			wpa_printf(MSG_DEBUG, "EAP-AKA: Checkcode from peer "
				   "indicates that AKA/Identity messages were "
				   "used, but they were not");
			return -1;
		}
		return 0;
	}

	hash_len = data->eap_method == EAP_TYPE_AKA_PRIME ?
		EAP_AKA_PRIME_CHECKCODE_LEN : EAP_AKA_CHECKCODE_LEN;

	if (checkcode_len != hash_len) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Checkcode from peer indicates "
			   "that AKA/Identity message were not used, but they "
			   "were");
		return -1;
	}

	/* Checkcode is SHA1 hash over all EAP-AKA/Identity packets. */
	addr = wpabuf_head(data->id_msgs);
	len = wpabuf_len(data->id_msgs);
	if (data->eap_method == EAP_TYPE_AKA_PRIME)
		sha256_vector(1, &addr, &len, hash);
	else
		sha1_vector(1, &addr, &len, hash);

	if (os_memcmp_const(hash, checkcode, hash_len) != 0) {
		wpa_printf(MSG_DEBUG, "EAP-AKA: Mismatch in AT_CHECKCODE");
		return -1;
	}

	return 0;
}