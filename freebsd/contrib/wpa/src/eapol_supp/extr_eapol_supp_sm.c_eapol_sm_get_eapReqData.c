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
struct eapol_sm {struct wpabuf* eapReqData; } ;

/* Variables and functions */

__attribute__((used)) static struct wpabuf * eapol_sm_get_eapReqData(void *ctx)
{
	struct eapol_sm *sm = ctx;
	if (sm == NULL || sm->eapReqData == NULL)
		return NULL;

	return sm->eapReqData;
}