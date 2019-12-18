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
typedef  scalar_t__ u8 ;
struct radius_msg {int dummy; } ;
struct eapol_test_data {scalar_t__* eap_identity; size_t eap_identity_len; TYPE_1__* wpa_s; int /*<<< orphan*/  radius; int /*<<< orphan*/  last_recv_radius; int /*<<< orphan*/  extra_attrs; int /*<<< orphan*/  connect_info; int /*<<< orphan*/  own_ip_addr; scalar_t__ req_eap_key_name; int /*<<< orphan*/  radius_identifier; } ;
struct eap_hdr {scalar_t__ code; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ code; } ;
struct TYPE_3__ {int /*<<< orphan*/  own_addr; } ;

/* Variables and functions */
 scalar_t__ EAP_CODE_RESPONSE ; 
 scalar_t__ const EAP_TYPE_IDENTITY ; 
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 char* RADIUS_802_1X_ADDR_FORMAT ; 
 int /*<<< orphan*/  RADIUS_ATTR_CALLING_STATION_ID ; 
 int /*<<< orphan*/  RADIUS_ATTR_CONNECT_INFO ; 
 int /*<<< orphan*/  RADIUS_ATTR_EAP_KEY_NAME ; 
 int /*<<< orphan*/  RADIUS_ATTR_FRAMED_MTU ; 
 int /*<<< orphan*/  RADIUS_ATTR_NAS_IP_ADDRESS ; 
 int /*<<< orphan*/  RADIUS_ATTR_NAS_PORT_TYPE ; 
 int /*<<< orphan*/  RADIUS_ATTR_SERVICE_TYPE ; 
 int /*<<< orphan*/  RADIUS_ATTR_STATE ; 
 int /*<<< orphan*/  RADIUS_ATTR_USER_NAME ; 
 int /*<<< orphan*/  RADIUS_AUTH ; 
 scalar_t__ RADIUS_CODE_ACCESS_CHALLENGE ; 
 int /*<<< orphan*/  RADIUS_CODE_ACCESS_REQUEST ; 
 int /*<<< orphan*/  RADIUS_MAX_ATTR_LEN ; 
 int RADIUS_NAS_PORT_TYPE_IEEE_802_11 ; 
 int RADIUS_SERVICE_TYPE_FRAMED ; 
 scalar_t__ add_extra_attrs (struct radius_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_extra_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 scalar_t__* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (scalar_t__*,scalar_t__ const*,size_t) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int os_strlen (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  radius_client_get_id (int /*<<< orphan*/ ) ; 
 scalar_t__ radius_client_send (int /*<<< orphan*/ ,struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_add_attr (struct radius_msg*,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  radius_msg_add_attr_int32 (struct radius_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radius_msg_add_eap (struct radius_msg*,scalar_t__ const*,size_t) ; 
 int radius_msg_copy_attr (struct radius_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_free (struct radius_msg*) ; 
 TYPE_2__* radius_msg_get_hdr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radius_msg_make_authenticator (struct radius_msg*) ; 
 struct radius_msg* radius_msg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ieee802_1x_encapsulate_radius(struct eapol_test_data *e,
					  const u8 *eap, size_t len)
{
	struct radius_msg *msg;
	char buf[RADIUS_MAX_ATTR_LEN + 1];
	const struct eap_hdr *hdr;
	const u8 *pos;

	wpa_printf(MSG_DEBUG, "Encapsulating EAP message into a RADIUS "
		   "packet");

	e->radius_identifier = radius_client_get_id(e->radius);
	msg = radius_msg_new(RADIUS_CODE_ACCESS_REQUEST,
			     e->radius_identifier);
	if (msg == NULL) {
		printf("Could not create net RADIUS packet\n");
		return;
	}

	radius_msg_make_authenticator(msg);

	hdr = (const struct eap_hdr *) eap;
	pos = (const u8 *) (hdr + 1);
	if (len > sizeof(*hdr) && hdr->code == EAP_CODE_RESPONSE &&
	    pos[0] == EAP_TYPE_IDENTITY) {
		pos++;
		os_free(e->eap_identity);
		e->eap_identity_len = len - sizeof(*hdr) - 1;
		e->eap_identity = os_malloc(e->eap_identity_len);
		if (e->eap_identity) {
			os_memcpy(e->eap_identity, pos, e->eap_identity_len);
			wpa_hexdump(MSG_DEBUG, "Learned identity from "
				    "EAP-Response-Identity",
				    e->eap_identity, e->eap_identity_len);
		}
	}

	if (e->eap_identity &&
	    !radius_msg_add_attr(msg, RADIUS_ATTR_USER_NAME,
				 e->eap_identity, e->eap_identity_len)) {
		printf("Could not add User-Name\n");
		goto fail;
	}

	if (e->req_eap_key_name &&
	    !radius_msg_add_attr(msg, RADIUS_ATTR_EAP_KEY_NAME, (u8 *) "\0",
				 1)) {
		printf("Could not add EAP-Key-Name\n");
		goto fail;
	}

	if (!find_extra_attr(e->extra_attrs, RADIUS_ATTR_NAS_IP_ADDRESS) &&
	    !radius_msg_add_attr(msg, RADIUS_ATTR_NAS_IP_ADDRESS,
				 (u8 *) &e->own_ip_addr, 4)) {
		printf("Could not add NAS-IP-Address\n");
		goto fail;
	}

	os_snprintf(buf, sizeof(buf), RADIUS_802_1X_ADDR_FORMAT,
		    MAC2STR(e->wpa_s->own_addr));
	if (!find_extra_attr(e->extra_attrs, RADIUS_ATTR_CALLING_STATION_ID)
	    &&
	    !radius_msg_add_attr(msg, RADIUS_ATTR_CALLING_STATION_ID,
				 (u8 *) buf, os_strlen(buf))) {
		printf("Could not add Calling-Station-Id\n");
		goto fail;
	}

	/* TODO: should probably check MTU from driver config; 2304 is max for
	 * IEEE 802.11, but use 1400 to avoid problems with too large packets
	 */
	if (!find_extra_attr(e->extra_attrs, RADIUS_ATTR_FRAMED_MTU) &&
	    !radius_msg_add_attr_int32(msg, RADIUS_ATTR_FRAMED_MTU, 1400)) {
		printf("Could not add Framed-MTU\n");
		goto fail;
	}

	if (!find_extra_attr(e->extra_attrs, RADIUS_ATTR_NAS_PORT_TYPE) &&
	    !radius_msg_add_attr_int32(msg, RADIUS_ATTR_NAS_PORT_TYPE,
				       RADIUS_NAS_PORT_TYPE_IEEE_802_11)) {
		printf("Could not add NAS-Port-Type\n");
		goto fail;
	}

	if (!find_extra_attr(e->extra_attrs, RADIUS_ATTR_SERVICE_TYPE) &&
	    !radius_msg_add_attr_int32(msg, RADIUS_ATTR_SERVICE_TYPE,
				       RADIUS_SERVICE_TYPE_FRAMED)) {
		printf("Could not add Service-Type\n");
		goto fail;
	}

	os_snprintf(buf, sizeof(buf), "%s", e->connect_info);
	if (!find_extra_attr(e->extra_attrs, RADIUS_ATTR_CONNECT_INFO) &&
	    !radius_msg_add_attr(msg, RADIUS_ATTR_CONNECT_INFO,
				 (u8 *) buf, os_strlen(buf))) {
		printf("Could not add Connect-Info\n");
		goto fail;
	}

	if (add_extra_attrs(msg, e->extra_attrs) < 0)
		goto fail;

	if (eap && !radius_msg_add_eap(msg, eap, len)) {
		printf("Could not add EAP-Message\n");
		goto fail;
	}

	/* State attribute must be copied if and only if this packet is
	 * Access-Request reply to the previous Access-Challenge */
	if (e->last_recv_radius &&
	    radius_msg_get_hdr(e->last_recv_radius)->code ==
	    RADIUS_CODE_ACCESS_CHALLENGE) {
		int res = radius_msg_copy_attr(msg, e->last_recv_radius,
					       RADIUS_ATTR_STATE);
		if (res < 0) {
			printf("Could not copy State attribute from previous "
			       "Access-Challenge\n");
			goto fail;
		}
		if (res > 0) {
			wpa_printf(MSG_DEBUG, "  Copied RADIUS State "
				   "Attribute");
		}
	}

	if (radius_client_send(e->radius, msg, RADIUS_AUTH, e->wpa_s->own_addr)
	    < 0)
		goto fail;
	return;

 fail:
	radius_msg_free(msg);
}