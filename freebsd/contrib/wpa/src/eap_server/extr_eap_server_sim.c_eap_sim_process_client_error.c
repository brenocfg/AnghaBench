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
struct eap_sim_data {scalar_t__ notification; scalar_t__ use_result_ind; } ;
struct eap_sim_attrs {int /*<<< orphan*/  client_error_code; } ;

/* Variables and functions */
 scalar_t__ EAP_SIM_SUCCESS ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  eap_sim_state (struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_sim_process_client_error(struct eap_sm *sm,
					 struct eap_sim_data *data,
					 struct wpabuf *respData,
					 struct eap_sim_attrs *attr)
{
	wpa_printf(MSG_DEBUG, "EAP-SIM: Client reported error %d",
		   attr->client_error_code);
	if (data->notification == EAP_SIM_SUCCESS && data->use_result_ind)
		eap_sim_state(data, SUCCESS);
	else
		eap_sim_state(data, FAILURE);
}