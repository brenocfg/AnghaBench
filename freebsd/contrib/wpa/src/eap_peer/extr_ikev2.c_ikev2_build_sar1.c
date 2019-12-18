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
struct ikev2_transform {int type; int /*<<< orphan*/  transform_id; int /*<<< orphan*/  transform_type; int /*<<< orphan*/  transform_length; } ;
struct TYPE_2__ {size_t encr; size_t prf; size_t integ; size_t dh; int /*<<< orphan*/  proposal_num; } ;
struct ikev2_responder_data {TYPE_1__ proposal; } ;
struct ikev2_proposal {int num_transforms; int /*<<< orphan*/  proposal_length; int /*<<< orphan*/  protocol_id; int /*<<< orphan*/  proposal_num; } ;
struct ikev2_payload_hdr {int /*<<< orphan*/  payload_length; scalar_t__ flags; int /*<<< orphan*/  next_payload; } ;

/* Variables and functions */
 size_t ENCR_AES_CBC ; 
 int /*<<< orphan*/  IKEV2_PROTOCOL_IKE ; 
 int /*<<< orphan*/  IKEV2_TRANSFORM_DH ; 
 int /*<<< orphan*/  IKEV2_TRANSFORM_ENCR ; 
 int /*<<< orphan*/  IKEV2_TRANSFORM_INTEG ; 
 int /*<<< orphan*/  IKEV2_TRANSFORM_PRF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 void* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_be16 (struct wpabuf*,int) ; 

__attribute__((used)) static int ikev2_build_sar1(struct ikev2_responder_data *data,
			    struct wpabuf *msg, u8 next_payload)
{
	struct ikev2_payload_hdr *phdr;
	size_t plen;
	struct ikev2_proposal *p;
	struct ikev2_transform *t;

	wpa_printf(MSG_DEBUG, "IKEV2: Adding SAr1 payload");

	/* SAr1 - RFC 4306, Sect. 2.7 and 3.3 */
	phdr = wpabuf_put(msg, sizeof(*phdr));
	phdr->next_payload = next_payload;
	phdr->flags = 0;

	p = wpabuf_put(msg, sizeof(*p));
	p->proposal_num = data->proposal.proposal_num;
	p->protocol_id = IKEV2_PROTOCOL_IKE;
	p->num_transforms = 4;

	t = wpabuf_put(msg, sizeof(*t));
	t->type = 3;
	t->transform_type = IKEV2_TRANSFORM_ENCR;
	WPA_PUT_BE16(t->transform_id, data->proposal.encr);
	if (data->proposal.encr == ENCR_AES_CBC) {
		/* Transform Attribute: Key Len = 128 bits */
		wpabuf_put_be16(msg, 0x800e); /* AF=1, AttrType=14 */
		wpabuf_put_be16(msg, 128); /* 128-bit key */
	}
	plen = (u8 *) wpabuf_put(msg, 0) - (u8 *) t;
	WPA_PUT_BE16(t->transform_length, plen);

	t = wpabuf_put(msg, sizeof(*t));
	t->type = 3;
	WPA_PUT_BE16(t->transform_length, sizeof(*t));
	t->transform_type = IKEV2_TRANSFORM_PRF;
	WPA_PUT_BE16(t->transform_id, data->proposal.prf);

	t = wpabuf_put(msg, sizeof(*t));
	t->type = 3;
	WPA_PUT_BE16(t->transform_length, sizeof(*t));
	t->transform_type = IKEV2_TRANSFORM_INTEG;
	WPA_PUT_BE16(t->transform_id, data->proposal.integ);

	t = wpabuf_put(msg, sizeof(*t));
	WPA_PUT_BE16(t->transform_length, sizeof(*t));
	t->transform_type = IKEV2_TRANSFORM_DH;
	WPA_PUT_BE16(t->transform_id, data->proposal.dh);

	plen = (u8 *) wpabuf_put(msg, 0) - (u8 *) p;
	WPA_PUT_BE16(p->proposal_length, plen);

	plen = (u8 *) wpabuf_put(msg, 0) - (u8 *) phdr;
	WPA_PUT_BE16(phdr->payload_length, plen);

	return 0;
}