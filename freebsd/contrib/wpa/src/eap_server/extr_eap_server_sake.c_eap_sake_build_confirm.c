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
struct eap_sm {int /*<<< orphan*/  server_id_len; int /*<<< orphan*/  server_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  auth; } ;
struct eap_sake_data {void* state; int /*<<< orphan*/  peerid_len; int /*<<< orphan*/  peerid; int /*<<< orphan*/  rand_p; int /*<<< orphan*/  rand_s; TYPE_1__ tek; } ;

/* Variables and functions */
 scalar_t__ EAP_SAKE_AT_MIC_S ; 
 scalar_t__ EAP_SAKE_MIC_LEN ; 
 int /*<<< orphan*/  EAP_SAKE_SUBTYPE_CONFIRM ; 
 void* FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 struct wpabuf* eap_sake_build_msg (struct eap_sake_data*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sake_compute_mic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/ * wpabuf_put (struct wpabuf*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_put_u8 (struct wpabuf*,scalar_t__) ; 

__attribute__((used)) static struct wpabuf * eap_sake_build_confirm(struct eap_sm *sm,
					      struct eap_sake_data *data,
					      u8 id)
{
	struct wpabuf *msg;
	u8 *mic;

	wpa_printf(MSG_DEBUG, "EAP-SAKE: Request/Confirm");

	msg = eap_sake_build_msg(data, id, 2 + EAP_SAKE_MIC_LEN,
				 EAP_SAKE_SUBTYPE_CONFIRM);
	if (msg == NULL) {
		data->state = FAILURE;
		return NULL;
	}

	wpa_printf(MSG_DEBUG, "EAP-SAKE: * AT_MIC_S");
	wpabuf_put_u8(msg, EAP_SAKE_AT_MIC_S);
	wpabuf_put_u8(msg, 2 + EAP_SAKE_MIC_LEN);
	mic = wpabuf_put(msg, EAP_SAKE_MIC_LEN);
	if (eap_sake_compute_mic(data->tek.auth, data->rand_s, data->rand_p,
				 sm->server_id, sm->server_id_len,
				 data->peerid, data->peerid_len, 0,
				 wpabuf_head(msg), wpabuf_len(msg), mic, mic))
	{
		wpa_printf(MSG_INFO, "EAP-SAKE: Failed to compute MIC");
		data->state = FAILURE;
		wpabuf_free(msg);
		return NULL;
	}

	return msg;
}