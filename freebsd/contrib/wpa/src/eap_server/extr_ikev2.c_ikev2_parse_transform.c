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
typedef  void* u16 ;
struct ikev2_transform {int type; int transform_type; int /*<<< orphan*/  const* transform_id; int /*<<< orphan*/  const* transform_length; } ;
struct ikev2_proposal_data {void* dh; void* integ; void* prf; void* encr; } ;
struct TYPE_2__ {void* encr; void* prf; void* integ; void* dh; } ;
struct ikev2_initiator_data {TYPE_1__ proposal; } ;

/* Variables and functions */
 void* ENCR_AES_CBC ; 
#define  IKEV2_TRANSFORM_DH 131 
#define  IKEV2_TRANSFORM_ENCR 130 
#define  IKEV2_TRANSFORM_INTEG 129 
#define  IKEV2_TRANSFORM_PRF 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int WPA_GET_BE16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dh_groups_get (void*) ; 
 int /*<<< orphan*/  ikev2_get_encr (void*) ; 
 int /*<<< orphan*/  ikev2_get_integ (void*) ; 
 int /*<<< orphan*/  ikev2_get_prf (void*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int ikev2_parse_transform(struct ikev2_initiator_data *data,
				 struct ikev2_proposal_data *prop,
				 const u8 *pos, const u8 *end)
{
	int transform_len;
	const struct ikev2_transform *t;
	u16 transform_id;
	const u8 *tend;

	if (end - pos < (int) sizeof(*t)) {
		wpa_printf(MSG_INFO, "IKEV2: Too short transform");
		return -1;
	}

	t = (const struct ikev2_transform *) pos;
	transform_len = WPA_GET_BE16(t->transform_length);
	if (transform_len < (int) sizeof(*t) || transform_len > end - pos) {
		wpa_printf(MSG_INFO, "IKEV2: Invalid transform length %d",
			   transform_len);
		return -1;
	}
	tend = pos + transform_len;

	transform_id = WPA_GET_BE16(t->transform_id);

	wpa_printf(MSG_DEBUG, "IKEV2:   Transform:");
	wpa_printf(MSG_DEBUG, "IKEV2:     Type: %d  Transform Length: %d  "
		   "Transform Type: %d  Transform ID: %d",
		   t->type, transform_len, t->transform_type, transform_id);

	if (t->type != 0 && t->type != 3) {
		wpa_printf(MSG_INFO, "IKEV2: Unexpected Transform type");
		return -1;
	}

	pos = (const u8 *) (t + 1);
	if (pos < tend) {
		wpa_hexdump(MSG_DEBUG, "IKEV2:     Transform Attributes",
			    pos, tend - pos);
	}

	switch (t->transform_type) {
	case IKEV2_TRANSFORM_ENCR:
		if (ikev2_get_encr(transform_id) &&
		    transform_id == data->proposal.encr) {
			if (transform_id == ENCR_AES_CBC) {
				if (tend - pos != 4) {
					wpa_printf(MSG_DEBUG, "IKEV2: No "
						   "Transform Attr for AES");
					break;
				}
				if (WPA_GET_BE16(pos) != 0x800e) {
					wpa_printf(MSG_DEBUG, "IKEV2: Not a "
						   "Key Size attribute for "
						   "AES");
					break;
				}
				if (WPA_GET_BE16(pos + 2) != 128) {
					wpa_printf(MSG_DEBUG, "IKEV2: "
						   "Unsupported AES key size "
						   "%d bits",
						   WPA_GET_BE16(pos + 2));
					break;
				}
			}
			prop->encr = transform_id;
		}
		break;
	case IKEV2_TRANSFORM_PRF:
		if (ikev2_get_prf(transform_id) &&
		    transform_id == data->proposal.prf)
			prop->prf = transform_id;
		break;
	case IKEV2_TRANSFORM_INTEG:
		if (ikev2_get_integ(transform_id) &&
		    transform_id == data->proposal.integ)
			prop->integ = transform_id;
		break;
	case IKEV2_TRANSFORM_DH:
		if (dh_groups_get(transform_id) &&
		    transform_id == data->proposal.dh)
			prop->dh = transform_id;
		break;
	}

	return transform_len;
}