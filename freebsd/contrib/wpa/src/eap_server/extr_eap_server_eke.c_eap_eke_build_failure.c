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
struct eap_eke_data {int /*<<< orphan*/  failure_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_EKE_FAILURE ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_eke_build_msg (struct eap_eke_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_eke_state (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_put_be32 (struct wpabuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wpabuf * eap_eke_build_failure(struct eap_eke_data *data, u8 id)
{
	struct wpabuf *msg;

	wpa_printf(MSG_DEBUG, "EAP-EKE: Request/Failure: Failure-Code=0x%x",
		   data->failure_code);

	msg = eap_eke_build_msg(data, id, 4, EAP_EKE_FAILURE);
	if (msg == NULL) {
		eap_eke_state(data, FAILURE);
		return NULL;
	}
	wpabuf_put_be32(msg, data->failure_code);

	return msg;
}