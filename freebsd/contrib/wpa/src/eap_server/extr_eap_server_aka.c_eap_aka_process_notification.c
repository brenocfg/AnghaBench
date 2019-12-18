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
struct eap_sim_attrs {int dummy; } ;
struct eap_aka_data {scalar_t__ notification; scalar_t__ use_result_ind; } ;

/* Variables and functions */
 scalar_t__ EAP_SIM_SUCCESS ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_aka_process_notification(struct eap_sm *sm,
					 struct eap_aka_data *data,
					 struct wpabuf *respData,
					 struct eap_sim_attrs *attr)
{
	wpa_printf(MSG_DEBUG, "EAP-AKA: Client replied to notification");
	if (data->notification == EAP_SIM_SUCCESS && data->use_result_ind)
		eap_aka_state(data, SUCCESS);
	else
		eap_aka_state(data, FAILURE);
}