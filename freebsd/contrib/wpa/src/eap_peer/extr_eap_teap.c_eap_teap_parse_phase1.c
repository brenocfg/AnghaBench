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
struct eap_teap_data {int max_pac_list_len; int use_pac_binary_format; int test_outer_tlvs; void* provisioning_allowed; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* atoi (char const*) ; 
 char* os_strstr (char const*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_teap_parse_phase1(struct eap_teap_data *data,
				  const char *phase1)
{
	const char *pos;

	pos = os_strstr(phase1, "teap_provisioning=");
	if (pos) {
		data->provisioning_allowed = atoi(pos + 18);
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Automatic PAC provisioning mode: %d",
			   data->provisioning_allowed);
	}

	pos = os_strstr(phase1, "teap_max_pac_list_len=");
	if (pos) {
		data->max_pac_list_len = atoi(pos + 22);
		if (data->max_pac_list_len == 0)
			data->max_pac_list_len = 1;
		wpa_printf(MSG_DEBUG, "EAP-TEAP: Maximum PAC list length: %lu",
			   (unsigned long) data->max_pac_list_len);
	}

	if (os_strstr(phase1, "teap_pac_format=binary")) {
		data->use_pac_binary_format = 1;
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Using binary format for PAC list");
	}

#ifdef CONFIG_TESTING_OPTIONS
	if (os_strstr(phase1, "teap_test_outer_tlvs=1"))
		data->test_outer_tlvs = 1;
#endif /* CONFIG_TESTING_OPTIONS */
}