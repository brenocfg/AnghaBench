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
struct eap_sm {scalar_t__ ssl_ctx; scalar_t__ ssl_ctx2; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_deinit_prev_method (struct eap_sm*,char*) ; 
 int /*<<< orphan*/  eap_peer_erp_free_keys (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_sm_abort (struct eap_sm*) ; 
 int /*<<< orphan*/  os_free (struct eap_sm*) ; 
 int /*<<< orphan*/  tls_deinit (scalar_t__) ; 

void eap_peer_sm_deinit(struct eap_sm *sm)
{
	if (sm == NULL)
		return;
	eap_deinit_prev_method(sm, "EAP deinit");
	eap_sm_abort(sm);
	if (sm->ssl_ctx2)
		tls_deinit(sm->ssl_ctx2);
	tls_deinit(sm->ssl_ctx);
	eap_peer_erp_free_keys(sm);
	os_free(sm);
}