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
struct eap_sm {int /*<<< orphan*/  eapol_ctx; TYPE_1__* eapol_cb; } ;
struct TYPE_2__ {int (* get_erp_send_reauth_start ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int eap_get_erp_send_reauth_start(struct eap_sm *sm)
{
	if (sm->eapol_cb->get_erp_send_reauth_start)
		return sm->eapol_cb->get_erp_send_reauth_start(sm->eapol_ctx);
	return 0;
}