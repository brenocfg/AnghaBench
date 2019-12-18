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
struct eapol_sm {int /*<<< orphan*/  eap; } ;

/* Variables and functions */
 struct wpabuf* eap_peer_build_erp_reauth_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct wpabuf * eapol_sm_build_erp_reauth_start(struct eapol_sm *sm)
{
#ifdef CONFIG_ERP
	if (!sm)
		return NULL;
	return eap_peer_build_erp_reauth_start(sm->eap, 0);
#else /* CONFIG_ERP */
	return NULL;
#endif /* CONFIG_ERP */
}