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
struct eap_aka_data {int state; scalar_t__ auts_reported; } ;

/* Variables and functions */
#define  CHALLENGE 131 
#define  IDENTITY 130 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  NOTIFICATION 129 
#define  REAUTH 128 
 struct wpabuf* eap_aka_build_challenge (struct eap_sm*,struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_aka_build_identity (struct eap_sm*,struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_aka_build_notification (struct eap_sm*,struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_aka_build_reauth (struct eap_sm*,struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct wpabuf * eap_aka_buildReq(struct eap_sm *sm, void *priv, u8 id)
{
	struct eap_aka_data *data = priv;

	data->auts_reported = 0;
	switch (data->state) {
	case IDENTITY:
		return eap_aka_build_identity(sm, data, id);
	case CHALLENGE:
		return eap_aka_build_challenge(sm, data, id);
	case REAUTH:
		return eap_aka_build_reauth(sm, data, id);
	case NOTIFICATION:
		return eap_aka_build_notification(sm, data, id);
	default:
		wpa_printf(MSG_DEBUG, "EAP-AKA: Unknown state %d in "
			   "buildReq", data->state);
		break;
	}
	return NULL;
}