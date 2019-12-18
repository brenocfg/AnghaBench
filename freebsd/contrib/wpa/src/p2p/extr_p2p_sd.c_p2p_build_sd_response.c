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
typedef  int /*<<< orphan*/  u16 ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANQP_VENDOR_SPECIFIC ; 
 int /*<<< orphan*/  P2P_IE_VENDOR_TYPE ; 
 int /*<<< orphan*/ * gas_anqp_add_element (struct wpabuf*,int /*<<< orphan*/ ) ; 
 struct wpabuf* gas_anqp_build_initial_resp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gas_anqp_set_element_len (struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gas_anqp_set_len (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * p2p_build_sd_response(u8 dialog_token, u16 status_code,
					     u16 comeback_delay,
					     u16 update_indic,
					     const struct wpabuf *tlvs)
{
	struct wpabuf *buf;
	u8 *len_pos;

	buf = gas_anqp_build_initial_resp(dialog_token, status_code,
					  comeback_delay,
					  100 + (tlvs ? wpabuf_len(tlvs) : 0));
	if (buf == NULL)
		return NULL;

	if (tlvs) {
		/* ANQP Query Response Frame */
		len_pos = gas_anqp_add_element(buf, ANQP_VENDOR_SPECIFIC);
		wpabuf_put_be32(buf, P2P_IE_VENDOR_TYPE);
		 /* Service Update Indicator */
		wpabuf_put_le16(buf, update_indic);
		wpabuf_put_buf(buf, tlvs);
		gas_anqp_set_element_len(buf, len_pos);
	}

	gas_anqp_set_len(buf);

	return buf;
}