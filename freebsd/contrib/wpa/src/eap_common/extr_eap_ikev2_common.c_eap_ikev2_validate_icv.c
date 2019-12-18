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
struct wpabuf {int dummy; } ;
struct ikev2_keys {int /*<<< orphan*/  SK_integ_len; int /*<<< orphan*/  const* SK_ar; int /*<<< orphan*/  const* SK_ai; } ;
struct ikev2_integ_alg {size_t hash_len; } ;

/* Variables and functions */
 int IKEV2_MAX_HASH_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct ikev2_integ_alg* ikev2_get_integ (int) ; 
 scalar_t__ ikev2_integ_hash (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf const*) ; 
 scalar_t__ wpabuf_len (struct wpabuf const*) ; 

int eap_ikev2_validate_icv(int integ_alg, struct ikev2_keys *keys,
			   int initiator, const struct wpabuf *msg,
			   const u8 *pos, const u8 *end)
{
	const struct ikev2_integ_alg *integ;
	size_t icv_len;
	u8 icv[IKEV2_MAX_HASH_LEN];
	const u8 *SK_a = initiator ? keys->SK_ai : keys->SK_ar;

	integ = ikev2_get_integ(integ_alg);
	if (integ == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-IKEV2: Unknown INTEG "
			   "transform / cannot validate ICV");
		return -1;
	}
	icv_len = integ->hash_len;

	if (end - pos < (int) icv_len) {
		wpa_printf(MSG_DEBUG, "EAP-IKEV2: Not enough room in the "
			   "message for Integrity Checksum Data");
		return -1;
	}

	if (SK_a == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-IKEV2: No SK_a for ICV validation");
		return -1;
	}

	if (ikev2_integ_hash(integ_alg, SK_a, keys->SK_integ_len,
			     wpabuf_head(msg),
			     wpabuf_len(msg) - icv_len, icv) < 0) {
		wpa_printf(MSG_INFO, "EAP-IKEV2: Could not calculate ICV");
		return -1;
	}

	if (os_memcmp_const(icv, end - icv_len, icv_len) != 0) {
		wpa_printf(MSG_INFO, "EAP-IKEV2: Invalid ICV");
		wpa_hexdump(MSG_DEBUG, "EAP-IKEV2: Calculated ICV",
			    icv, icv_len);
		wpa_hexdump(MSG_DEBUG, "EAP-IKEV2: Received ICV",
			    end - icv_len, icv_len);
		return -1;
	}

	wpa_printf(MSG_DEBUG, "EAP-IKEV2: Valid Integrity Checksum Data in "
		   "the received message");

	return icv_len;
}