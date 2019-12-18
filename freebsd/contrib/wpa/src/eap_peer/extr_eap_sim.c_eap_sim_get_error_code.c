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
struct eap_sim_data {int error_code; } ;

/* Variables and functions */
 int NO_EAP_METHOD_ERROR ; 

__attribute__((used)) static int eap_sim_get_error_code(void *priv)
{
	struct eap_sim_data *data = priv;
	int current_data_error;

	if (!data)
		return NO_EAP_METHOD_ERROR;

	current_data_error = data->error_code;

	/* Now reset for next transaction */
	data->error_code = NO_EAP_METHOD_ERROR;

	return current_data_error;
}