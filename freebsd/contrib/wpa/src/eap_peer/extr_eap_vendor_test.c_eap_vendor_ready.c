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
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_notify_pending (struct eap_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_vendor_ready(void *eloop_ctx, void *timeout_ctx)
{
	struct eap_sm *sm = eloop_ctx;
	wpa_printf(MSG_DEBUG, "EAP-VENDOR-TEST: Ready to re-process pending "
		   "request");
	eap_notify_pending(sm);
}