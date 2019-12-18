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
 struct wpabuf* gas_anqp_build_initial_req (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gas_anqp_set_element_len (struct wpabuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gas_anqp_set_len (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_le16 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * p2p_build_sd_query(u16 update_indic,
					  struct wpabuf *tlvs)
{
	struct wpabuf *buf;
	u8 *len_pos;

	buf = gas_anqp_build_initial_req(0, 100 + wpabuf_len(tlvs));
	if (buf == NULL)
		return NULL;

	/* ANQP Query Request Frame */
	len_pos = gas_anqp_add_element(buf, ANQP_VENDOR_SPECIFIC);
	wpabuf_put_be32(buf, P2P_IE_VENDOR_TYPE);
	wpabuf_put_le16(buf, update_indic); /* Service Update Indicator */
	wpabuf_put_buf(buf, tlvs);
	gas_anqp_set_element_len(buf, len_pos);

	gas_anqp_set_len(buf);

	return buf;
}