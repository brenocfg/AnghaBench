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
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_tls_data {int state; TYPE_1__ ssl; } ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_tls_state_txt (int) ; 
 int /*<<< orphan*/  tls_connection_remove_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_tls_state(struct eap_tls_data *data, int state)
{
	wpa_printf(MSG_DEBUG, "EAP-TLS: %s -> %s",
		   eap_tls_state_txt(data->state),
		   eap_tls_state_txt(state));
	data->state = state;
	if (state == FAILURE)
		tls_connection_remove_session(data->ssl.conn);
}