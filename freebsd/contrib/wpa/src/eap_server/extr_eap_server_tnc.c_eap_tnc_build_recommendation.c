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
struct wpabuf {int dummy; } ;
struct eap_tnc_data {int recommendation; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
#define  ALLOW 131 
 int /*<<< orphan*/  DONE ; 
 int /*<<< orphan*/  FAIL ; 
#define  ISOLATE 130 
 int /*<<< orphan*/  MSG_DEBUG ; 
#define  NO_ACCESS 129 
#define  NO_RECOMMENDATION 128 
 struct wpabuf* eap_tnc_build (struct eap_sm*,struct eap_tnc_data*) ; 
 int /*<<< orphan*/  eap_tnc_set_state (struct eap_tnc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct wpabuf * eap_tnc_build_recommendation(struct eap_sm *sm,
						    struct eap_tnc_data *data)
{
	switch (data->recommendation) {
	case ALLOW:
		eap_tnc_set_state(data, DONE);
		break;
	case ISOLATE:
		eap_tnc_set_state(data, FAIL);
		/* TODO: support assignment to a different VLAN */
		break;
	case NO_ACCESS:
		eap_tnc_set_state(data, FAIL);
		break;
	case NO_RECOMMENDATION:
		eap_tnc_set_state(data, DONE);
		break;
	default:
		wpa_printf(MSG_DEBUG, "EAP-TNC: Unknown recommendation");
		return NULL;
	}

	return eap_tnc_build(sm, data);
}