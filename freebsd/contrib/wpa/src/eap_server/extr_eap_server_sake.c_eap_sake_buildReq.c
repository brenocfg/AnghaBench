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
struct eap_sake_data {int state; } ;

/* Variables and functions */
#define  CHALLENGE 130 
#define  CONFIRM 129 
#define  IDENTITY 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 struct wpabuf* eap_sake_build_challenge (struct eap_sm*,struct eap_sake_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sake_build_confirm (struct eap_sm*,struct eap_sake_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_sake_build_identity (struct eap_sm*,struct eap_sake_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct wpabuf * eap_sake_buildReq(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_sake_data *data = priv;

	switch (data->state) {
	case IDENTITY:
		return eap_sake_build_identity(sm, data, id);
	case CHALLENGE:
		return eap_sake_build_challenge(sm, data, id);
	case CONFIRM:
		return eap_sake_build_confirm(sm, data, id);
	default:
		wpa_printf(MSG_DEBUG, "EAP-SAKE: Unknown state %d in buildReq",
			   data->state);
		break;
	}
	return NULL;
}