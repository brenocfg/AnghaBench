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
struct eap_method_ret {int dummy; } ;
struct eap_eke_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_EKE_FAIL_NO_ERROR ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_GET_BE32 (int /*<<< orphan*/  const*) ; 
 struct wpabuf* eap_eke_build_fail (struct eap_eke_data*,struct eap_method_ret*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_get_id (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_eke_process_failure(struct eap_eke_data *data,
					       struct eap_method_ret *ret,
					       const struct wpabuf *reqData,
					       const u8 *payload,
					       size_t payload_len)
{
	wpa_printf(MSG_DEBUG, "EAP-EKE: Received EAP-EKE-Failure/Request");

	if (payload_len < 4) {
		wpa_printf(MSG_DEBUG, "EAP-EKE: Too short EAP-EKE-Failure");
	} else {
		u32 code;
		code = WPA_GET_BE32(payload);
		wpa_printf(MSG_INFO, "EAP-EKE: Failure-Code 0x%x", code);
	}

	return eap_eke_build_fail(data, ret, eap_get_id(reqData),
				  EAP_EKE_FAIL_NO_ERROR);
}