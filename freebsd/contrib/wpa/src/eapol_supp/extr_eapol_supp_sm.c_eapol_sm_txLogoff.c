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
typedef  int /*<<< orphan*/  u8 ;
struct eapol_sm {int /*<<< orphan*/  dot1xSuppEapolFramesTx; int /*<<< orphan*/  dot1xSuppEapolLogoffFramesTx; TYPE_1__* ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  eapol_send_ctx; int /*<<< orphan*/  (* eapol_send ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAPOL_LOGOFF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eapol_sm_txLogoff(struct eapol_sm *sm)
{
	wpa_printf(MSG_DEBUG, "EAPOL: txLogoff");
	sm->ctx->eapol_send(sm->ctx->eapol_send_ctx,
			    IEEE802_1X_TYPE_EAPOL_LOGOFF, (u8 *) "", 0);
	sm->dot1xSuppEapolLogoffFramesTx++;
	sm->dot1xSuppEapolFramesTx++;
}