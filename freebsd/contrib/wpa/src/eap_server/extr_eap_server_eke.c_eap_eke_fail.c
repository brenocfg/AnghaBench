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
typedef  int /*<<< orphan*/  u32 ;
struct eap_eke_data {int /*<<< orphan*/  failure_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE_REPORT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_eke_state (struct eap_eke_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_eke_fail(struct eap_eke_data *data, u32 code)
{
	wpa_printf(MSG_DEBUG, "EAP-EKE: Failure - code 0x%x", code);
	data->failure_code = code;
	eap_eke_state(data, FAILURE_REPORT);
}