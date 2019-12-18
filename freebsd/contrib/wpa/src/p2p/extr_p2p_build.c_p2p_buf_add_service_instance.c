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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;
struct p2ps_advertisement {int /*<<< orphan*/  svc_name; int /*<<< orphan*/  config_methods; int /*<<< orphan*/  id; int /*<<< orphan*/  hash; struct p2ps_advertisement* next; } ;
struct p2p_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_SVC_ADV_IE_LEN ; 
 size_t MAX_SVC_ADV_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ P2PS_HASH_LEN ; 
 int /*<<< orphan*/  P2PS_WILD_HASH_STR ; 
 int /*<<< orphan*/  P2P_ATTR_ADVERTISED_SERVICE ; 
 int /*<<< orphan*/  WPA_PUT_LE16 (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (scalar_t__ const*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__* p2p_buf_add_ie_hdr (struct wpabuf*) ; 
 scalar_t__ p2p_buf_add_service_info (struct wpabuf*,struct p2p_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__**,scalar_t__**,size_t*,scalar_t__*) ; 
 int /*<<< orphan*/  p2p_buf_update_ie_hdr (struct wpabuf*,scalar_t__*) ; 
 scalar_t__ p2p_wfa_service_adv (struct p2p_data*) ; 
 scalar_t__ p2ps_wildcard_hash (struct p2p_data*,scalar_t__ const*,scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__ const*,scalar_t__) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 

void p2p_buf_add_service_instance(struct wpabuf *buf, struct p2p_data *p2p,
				  u8 hash_count, const u8 *hash,
				  struct p2ps_advertisement *adv_list)
{
	struct p2ps_advertisement *adv;
	int p2ps_wildcard;
	size_t total_len;
	struct wpabuf *tmp_buf = NULL;
	u8 *pos, *attr_len, *ie_len = NULL;

	if (!adv_list || !hash || !hash_count)
		return;

	wpa_hexdump(MSG_DEBUG, "P2PS: Probe Request service hash values",
		    hash, hash_count * P2PS_HASH_LEN);
	p2ps_wildcard = p2ps_wildcard_hash(p2p, hash, hash_count) &&
		p2p_wfa_service_adv(p2p);

	/* Allocate temp buffer, allowing for overflow of 1 instance */
	tmp_buf = wpabuf_alloc(MAX_SVC_ADV_IE_LEN + 256 + P2PS_HASH_LEN);
	if (!tmp_buf)
		return;

	/*
	 * Attribute data can be split into a number of IEs. Start with the
	 * first IE and the attribute headers here.
	 */
	ie_len = p2p_buf_add_ie_hdr(tmp_buf);

	total_len = 0;

	wpabuf_put_u8(tmp_buf, P2P_ATTR_ADVERTISED_SERVICE);
	attr_len = wpabuf_put(tmp_buf, sizeof(u16));
	WPA_PUT_LE16(attr_len, (u16) total_len);
	p2p_buf_update_ie_hdr(tmp_buf, ie_len);
	pos = wpabuf_put(tmp_buf, 0);

	if (p2ps_wildcard) {
		/* org.wi-fi.wfds match found */
		p2p_buf_add_service_info(tmp_buf, p2p, 0, 0, P2PS_WILD_HASH_STR,
					 &ie_len, &pos, &total_len, attr_len);
	}

	/* add advertised service info of matching services */
	for (adv = adv_list; adv && total_len <= MAX_SVC_ADV_LEN;
	     adv = adv->next) {
		const u8 *test = hash;
		u8 i;

		for (i = 0; i < hash_count; i++) {
			/* exact name hash match */
			if (os_memcmp(test, adv->hash, P2PS_HASH_LEN) == 0 &&
			    p2p_buf_add_service_info(tmp_buf, p2p,
						     adv->id,
						     adv->config_methods,
						     adv->svc_name,
						     &ie_len, &pos,
						     &total_len,
						     attr_len))
				break;

			test += P2PS_HASH_LEN;
		}
	}

	if (total_len)
		wpabuf_put_buf(buf, tmp_buf);
	wpabuf_free(tmp_buf);
}