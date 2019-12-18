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
struct wpa_supplicant {TYPE_1__* conf; } ;
struct wpa_cred {scalar_t__ roaming_consortium_len; scalar_t__ realm; int /*<<< orphan*/  eap_method; scalar_t__ imsi; scalar_t__ pcsc; struct wpa_cred* next; } ;
struct TYPE_2__ {struct wpa_cred* cred; } ;

/* Variables and functions */

__attribute__((used)) static int cred_with_nai_realm(struct wpa_supplicant *wpa_s)
{
	struct wpa_cred *cred;

	for (cred = wpa_s->conf->cred; cred; cred = cred->next) {
		if (cred->pcsc || cred->imsi)
			continue;
		if (!cred->eap_method)
			return 1;
		if (cred->realm && cred->roaming_consortium_len == 0)
			return 1;
	}
	return 0;
}