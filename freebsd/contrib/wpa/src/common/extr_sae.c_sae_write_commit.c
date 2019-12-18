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
struct wpabuf {int dummy; } ;
struct sae_data {TYPE_1__* tmp; int /*<<< orphan*/  group; } ;
struct TYPE_2__ {int prime_len; int /*<<< orphan*/  own_commit_element_ffc; int /*<<< orphan*/  own_commit_element_ecc; scalar_t__ ec; int /*<<< orphan*/  own_commit_scalar; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WLAN_EID_EXTENSION ; 
 scalar_t__ WLAN_EID_EXT_PASSWORD_IDENTIFIER ; 
 int /*<<< orphan*/  crypto_bignum_to_bin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  crypto_ec_point_to_bin (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ os_strlen (char const*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf const*) ; 
 int wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char const*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

void sae_write_commit(struct sae_data *sae, struct wpabuf *buf,
		      const struct wpabuf *token, const char *identifier)
{
	u8 *pos;

	if (sae->tmp == NULL)
		return;

	wpabuf_put_le16(buf, sae->group); /* Finite Cyclic Group */
	if (token) {
		wpabuf_put_buf(buf, token);
		wpa_hexdump(MSG_DEBUG, "SAE: Anti-clogging token",
			    wpabuf_head(token), wpabuf_len(token));
	}
	pos = wpabuf_put(buf, sae->tmp->prime_len);
	crypto_bignum_to_bin(sae->tmp->own_commit_scalar, pos,
			     sae->tmp->prime_len, sae->tmp->prime_len);
	wpa_hexdump(MSG_DEBUG, "SAE: own commit-scalar",
		    pos, sae->tmp->prime_len);
	if (sae->tmp->ec) {
		pos = wpabuf_put(buf, 2 * sae->tmp->prime_len);
		crypto_ec_point_to_bin(sae->tmp->ec,
				       sae->tmp->own_commit_element_ecc,
				       pos, pos + sae->tmp->prime_len);
		wpa_hexdump(MSG_DEBUG, "SAE: own commit-element(x)",
			    pos, sae->tmp->prime_len);
		wpa_hexdump(MSG_DEBUG, "SAE: own commit-element(y)",
			    pos + sae->tmp->prime_len, sae->tmp->prime_len);
	} else {
		pos = wpabuf_put(buf, sae->tmp->prime_len);
		crypto_bignum_to_bin(sae->tmp->own_commit_element_ffc, pos,
				     sae->tmp->prime_len, sae->tmp->prime_len);
		wpa_hexdump(MSG_DEBUG, "SAE: own commit-element",
			    pos, sae->tmp->prime_len);
	}

	if (identifier) {
		/* Password Identifier element */
		wpabuf_put_u8(buf, WLAN_EID_EXTENSION);
		wpabuf_put_u8(buf, 1 + os_strlen(identifier));
		wpabuf_put_u8(buf, WLAN_EID_EXT_PASSWORD_IDENTIFIER);
		wpabuf_put_str(buf, identifier);
		wpa_printf(MSG_DEBUG, "SAE: own Password Identifier: %s",
			   identifier);
	}
}