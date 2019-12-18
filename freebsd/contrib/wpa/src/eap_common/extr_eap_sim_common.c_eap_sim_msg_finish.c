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
struct eap_sim_msg {int mac; struct wpabuf* buf; } ;
struct eap_hdr {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int EAP_TYPE_AKA_PRIME ; 
 int /*<<< orphan*/  eap_sim_add_mac (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  eap_sim_add_mac_sha256 (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  host_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct eap_sim_msg*) ; 
 scalar_t__ wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 struct eap_hdr* wpabuf_mhead (struct wpabuf*) ; 

struct wpabuf * eap_sim_msg_finish(struct eap_sim_msg *msg, int type,
				   const u8 *k_aut,
				   const u8 *extra, size_t extra_len)
{
	struct eap_hdr *eap;
	struct wpabuf *buf;

	if (msg == NULL)
		return NULL;

	eap = wpabuf_mhead(msg->buf);
	eap->length = host_to_be16(wpabuf_len(msg->buf));

#if defined(EAP_AKA_PRIME) || defined(EAP_SERVER_AKA_PRIME)
	if (k_aut && msg->mac && type == EAP_TYPE_AKA_PRIME) {
		eap_sim_add_mac_sha256(k_aut, (u8 *) wpabuf_head(msg->buf),
				       wpabuf_len(msg->buf),
				       (u8 *) wpabuf_mhead(msg->buf) +
				       msg->mac, extra, extra_len);
	} else
#endif /* EAP_AKA_PRIME || EAP_SERVER_AKA_PRIME */
	if (k_aut && msg->mac) {
		eap_sim_add_mac(k_aut, (u8 *) wpabuf_head(msg->buf),
				wpabuf_len(msg->buf),
				(u8 *) wpabuf_mhead(msg->buf) + msg->mac,
				extra, extra_len);
	}

	buf = msg->buf;
	os_free(msg);
	return buf;
}