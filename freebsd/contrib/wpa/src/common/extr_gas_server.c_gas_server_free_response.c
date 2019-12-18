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
struct gas_server_response {int /*<<< orphan*/  resp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct gas_server_response*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gas_server_response_timeout ; 
 int /*<<< orphan*/  os_free (struct gas_server_response*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct gas_server_response*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gas_server_free_response(struct gas_server_response *response)
{
	if (!response)
		return;
	wpa_printf(MSG_DEBUG, "DPP: Free GAS response @%p", response);
	eloop_cancel_timeout(gas_server_response_timeout, response, NULL);
	wpabuf_free(response->resp);
	os_free(response);
}