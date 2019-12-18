#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dh; } ;
struct ikev2_responder_data {TYPE_2__* dh; TYPE_1__ proposal; int /*<<< orphan*/  r_dh_private; } ;
struct ikev2_payload_hdr {int /*<<< orphan*/  payload_length; scalar_t__ flags; int /*<<< orphan*/  next_payload; } ;
struct TYPE_4__ {int prime_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,size_t) ; 
 struct wpabuf* dh_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int wpabuf_len (struct wpabuf*) ; 
 struct ikev2_payload_hdr* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 

__attribute__((used)) static int ikev2_build_ker(struct ikev2_responder_data *data,
			   struct wpabuf *msg, u8 next_payload)
{
	struct ikev2_payload_hdr *phdr;
	size_t plen;
	struct wpabuf *pv;

	wpa_printf(MSG_DEBUG, "IKEV2: Adding KEr payload");

	pv = dh_init(data->dh, &data->r_dh_private);
	if (pv == NULL) {
		wpa_printf(MSG_DEBUG, "IKEV2: Failed to initialize DH");
		return -1;
	}

	/* KEr - RFC 4306, Sect. 3.4 */
	phdr = wpabuf_put(msg, sizeof(*phdr));
	phdr->next_payload = next_payload;
	phdr->flags = 0;

	wpabuf_put_be16(msg, data->proposal.dh); /* DH Group # */
	wpabuf_put(msg, 2); /* RESERVED */
	/*
	 * RFC 4306, Sect. 3.4: possible zero padding for public value to
	 * match the length of the prime.
	 */
	wpabuf_put(msg, data->dh->prime_len - wpabuf_len(pv));
	wpabuf_put_buf(msg, pv);
	wpabuf_free(pv);

	plen = (u8 *) wpabuf_put(msg, 0) - (u8 *) phdr;
	WPA_PUT_BE16(phdr->payload_length, plen);
	return 0;
}