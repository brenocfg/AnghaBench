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
struct wpa_sm {scalar_t__ preauth_eapol; void* scard_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_sm_register_scard_ctx (scalar_t__,void*) ; 

void wpa_sm_set_scard_ctx(struct wpa_sm *sm, void *scard_ctx)
{
	if (sm == NULL)
		return;
	sm->scard_ctx = scard_ctx;
	if (sm->preauth_eapol)
		eapol_sm_register_scard_ctx(sm->preauth_eapol, scard_ctx);
}