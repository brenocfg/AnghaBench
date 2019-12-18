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
struct eap_sm {int dummy; } ;
struct eap_pax_data {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ PAX_STD_3 ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_pax_process_ack(struct eap_sm *sm,
				struct eap_pax_data *data,
				struct wpabuf *respData)
{
	if (data->state != PAX_STD_3)
		return;

	wpa_printf(MSG_DEBUG, "EAP-PAX: Received PAX-ACK - authentication "
		   "completed successfully");
	data->state = SUCCESS;
}