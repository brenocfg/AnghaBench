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
struct eap_sm {struct wpabuf* eapRespData; } ;

/* Variables and functions */

struct wpabuf * eap_get_eapRespData(struct eap_sm *sm)
{
	struct wpabuf *resp;

	if (sm == NULL || sm->eapRespData == NULL)
		return NULL;

	resp = sm->eapRespData;
	sm->eapRespData = NULL;

	return resp;
}