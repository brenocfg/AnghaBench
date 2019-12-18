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
typedef  int /*<<< orphan*/  u32 ;
struct wpabuf {int dummy; } ;
struct ttls_avp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVP_PAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * eap_ttls_avp_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 struct wpabuf* wpabuf_alloc (scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 scalar_t__ wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_mhead (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put (struct wpabuf*,int) ; 

__attribute__((used)) static int eap_ttls_avp_encapsulate(struct wpabuf **resp, u32 avp_code,
				    int mandatory)
{
	struct wpabuf *msg;
	u8 *avp, *pos;

	msg = wpabuf_alloc(sizeof(struct ttls_avp) + wpabuf_len(*resp) + 4);
	if (msg == NULL) {
		wpabuf_clear_free(*resp);
		*resp = NULL;
		return -1;
	}

	avp = wpabuf_mhead(msg);
	pos = eap_ttls_avp_hdr(avp, avp_code, 0, mandatory, wpabuf_len(*resp));
	os_memcpy(pos, wpabuf_head(*resp), wpabuf_len(*resp));
	pos += wpabuf_len(*resp);
	AVP_PAD(avp, pos);
	wpabuf_clear_free(*resp);
	wpabuf_put(msg, pos - avp);
	*resp = msg;
	return 0;
}