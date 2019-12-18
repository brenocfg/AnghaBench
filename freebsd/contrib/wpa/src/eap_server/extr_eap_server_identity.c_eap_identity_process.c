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
struct eap_sm {char* identity; size_t identity_len; int /*<<< orphan*/  update_user; } ;
struct eap_identity_data {void* state; scalar_t__ pick_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_IDENTITY ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 void* FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* SUCCESS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 scalar_t__ eap_identity_check (struct eap_sm*,struct eap_identity_data*,struct wpabuf*) ; 
 int /*<<< orphan*/  eap_log_msg (struct eap_sm*,char*,char*) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 void* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  printf_encode (char*,size_t,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_identity_process(struct eap_sm *sm, void *priv,
				 struct wpabuf *respData)
{
	struct eap_identity_data *data = priv;
	const u8 *pos;
	size_t len;
	char *buf;

	if (data->pick_up) {
		if (eap_identity_check(sm, data, respData)) {
			wpa_printf(MSG_DEBUG, "EAP-Identity: failed to pick "
				   "up already started negotiation");
			data->state = FAILURE;
			return;
		}
		data->pick_up = 0;
	}

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_IDENTITY,
			       respData, &len);
	if (pos == NULL)
		return; /* Should not happen - frame already validated */

	wpa_hexdump_ascii(MSG_DEBUG, "EAP-Identity: Peer identity", pos, len);
	buf = os_malloc(len * 4 + 1);
	if (buf) {
		printf_encode(buf, len * 4 + 1, pos, len);
		eap_log_msg(sm, "EAP-Response/Identity '%s'", buf);
		os_free(buf);
	}
	if (sm->identity)
		sm->update_user = TRUE;
	os_free(sm->identity);
	sm->identity = os_malloc(len ? len : 1);
	if (sm->identity == NULL) {
		data->state = FAILURE;
	} else {
		os_memcpy(sm->identity, pos, len);
		sm->identity_len = len;
		data->state = SUCCESS;
	}
}