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
struct wpabuf {int dummy; } ;
struct dpp_configurator {int own; char* kid; int /*<<< orphan*/  csign; int /*<<< orphan*/ * curve; } ;
typedef  int /*<<< orphan*/  kid_hash ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int SHA256_MAC_LEN ; 
 scalar_t__ base64_url_encode (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpp_configurator_free (struct dpp_configurator*) ; 
 int /*<<< orphan*/ * dpp_curves ; 
 int /*<<< orphan*/  dpp_gen_keypair (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dpp_get_curve_name (char const*) ; 
 struct wpabuf* dpp_get_pubkey_point (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dpp_set_keypair (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  os_free (struct dpp_configurator*) ; 
 struct dpp_configurator* os_zalloc (int) ; 
 scalar_t__ sha256_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 

struct dpp_configurator *
dpp_keygen_configurator(const char *curve, const u8 *privkey,
			size_t privkey_len)
{
	struct dpp_configurator *conf;
	struct wpabuf *csign_pub = NULL;
	u8 kid_hash[SHA256_MAC_LEN];
	const u8 *addr[1];
	size_t len[1];

	conf = os_zalloc(sizeof(*conf));
	if (!conf)
		return NULL;

	if (!curve) {
		conf->curve = &dpp_curves[0];
	} else {
		conf->curve = dpp_get_curve_name(curve);
		if (!conf->curve) {
			wpa_printf(MSG_INFO, "DPP: Unsupported curve: %s",
				   curve);
			os_free(conf);
			return NULL;
		}
	}
	if (privkey)
		conf->csign = dpp_set_keypair(&conf->curve, privkey,
					      privkey_len);
	else
		conf->csign = dpp_gen_keypair(conf->curve);
	if (!conf->csign)
		goto fail;
	conf->own = 1;

	csign_pub = dpp_get_pubkey_point(conf->csign, 1);
	if (!csign_pub) {
		wpa_printf(MSG_INFO, "DPP: Failed to extract C-sign-key");
		goto fail;
	}

	/* kid = SHA256(ANSI X9.63 uncompressed C-sign-key) */
	addr[0] = wpabuf_head(csign_pub);
	len[0] = wpabuf_len(csign_pub);
	if (sha256_vector(1, addr, len, kid_hash) < 0) {
		wpa_printf(MSG_DEBUG,
			   "DPP: Failed to derive kid for C-sign-key");
		goto fail;
	}

	conf->kid = (char *) base64_url_encode(kid_hash, sizeof(kid_hash),
					       NULL, 0);
	if (!conf->kid)
		goto fail;
out:
	wpabuf_free(csign_pub);
	return conf;
fail:
	dpp_configurator_free(conf);
	conf = NULL;
	goto out;
}