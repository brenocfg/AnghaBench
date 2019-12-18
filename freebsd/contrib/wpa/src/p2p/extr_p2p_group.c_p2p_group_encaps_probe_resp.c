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

/* Variables and functions */
 int /*<<< orphan*/  P2P_IE_VENDOR_TYPE ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 struct wpabuf* wpabuf_alloc (size_t) ; 
 int /*<<< orphan*/ * wpabuf_head (struct wpabuf*) ; 
 size_t wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,int) ; 

__attribute__((used)) static struct wpabuf * p2p_group_encaps_probe_resp(struct wpabuf *subelems)
{
	struct wpabuf *ie;
	const u8 *pos, *end;
	size_t len;

	if (subelems == NULL)
		return NULL;

	len = wpabuf_len(subelems) + 100;

	ie = wpabuf_alloc(len);
	if (ie == NULL)
		return NULL;

	pos = wpabuf_head(subelems);
	end = pos + wpabuf_len(subelems);

	while (end > pos) {
		size_t frag_len = end - pos;
		if (frag_len > 251)
			frag_len = 251;
		wpabuf_put_u8(ie, WLAN_EID_VENDOR_SPECIFIC);
		wpabuf_put_u8(ie, 4 + frag_len);
		wpabuf_put_be32(ie, P2P_IE_VENDOR_TYPE);
		wpabuf_put_data(ie, pos, frag_len);
		pos += frag_len;
	}

	return ie;
}