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
struct eap_sm {int dummy; } ;
struct eap_gpsk_data {int state; } ;

/* Variables and functions */
#define  GPSK_1 129 
#define  GPSK_3 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_gpsk_build_gpsk_1 (struct eap_sm*,struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_gpsk_build_gpsk_3 (struct eap_sm*,struct eap_gpsk_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct wpabuf * eap_gpsk_buildReq(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_gpsk_data *data = priv;

	switch (data->state) {
	case GPSK_1:
		return eap_gpsk_build_gpsk_1(sm, data, id);
	case GPSK_3:
		return eap_gpsk_build_gpsk_3(sm, data, id);
	default:
		wpa_printf(MSG_DEBUG, "EAP-GPSK: Unknown state %d in buildReq",
			   data->state);
		break;
	}
	return NULL;
}