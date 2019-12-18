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
typedef  int /*<<< orphan*/  u64 ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  P2P_SERV_P2PS ; 
 size_t os_strlen (char const*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_p2p_sd_request (struct wpa_supplicant*,int /*<<< orphan*/  const*,struct wpabuf*) ; 

u64 wpas_p2p_sd_request_asp(struct wpa_supplicant *wpa_s, const u8 *dst, u8 id,
			    const char *svc_str, const char *info_substr)
{
	struct wpabuf *tlvs;
	size_t plen, svc_len, substr_len = 0;
	u64 ret;

	svc_len = os_strlen(svc_str);
	if (info_substr)
		substr_len = os_strlen(info_substr);

	if (svc_len > 0xff || substr_len > 0xff)
		return 0;

	plen = 1 + 1 + 1 + svc_len + 1 + substr_len;
	tlvs = wpabuf_alloc(2 + plen);
	if (tlvs == NULL)
		return 0;

	wpabuf_put_le16(tlvs, plen);
	wpabuf_put_u8(tlvs, P2P_SERV_P2PS);
	wpabuf_put_u8(tlvs, id); /* Service Transaction ID */
	wpabuf_put_u8(tlvs, (u8) svc_len); /* Service String Length */
	wpabuf_put_data(tlvs, svc_str, svc_len);
	wpabuf_put_u8(tlvs, (u8) substr_len); /* Info Substring Length */
	wpabuf_put_data(tlvs, info_substr, substr_len);
	ret = wpas_p2p_sd_request(wpa_s, dst, tlvs);
	wpabuf_free(tlvs);

	return ret;
}