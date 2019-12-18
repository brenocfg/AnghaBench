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

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int get_cmd_arg_num (char const*,int) ; 
 char** os_calloc (int,int) ; 
 char* os_strdup (char const*) ; 

__attribute__((used)) static char ** hostapd_complete_set(const char *str, int pos)
{
	int arg = get_cmd_arg_num(str, pos);
	const char *fields[] = {
#ifdef CONFIG_WPS_TESTING
		"wps_version_number", "wps_testing_dummy_cred",
		"wps_corrupt_pkhash",
#endif /* CONFIG_WPS_TESTING */
#ifdef CONFIG_INTERWORKING
		"gas_frag_limit",
#endif /* CONFIG_INTERWORKING */
#ifdef CONFIG_TESTING_OPTIONS
		"ext_mgmt_frame_handling", "ext_eapol_frame_io",
#endif /* CONFIG_TESTING_OPTIONS */
#ifdef CONFIG_MBO
		"mbo_assoc_disallow",
#endif /* CONFIG_MBO */
		"deny_mac_file", "accept_mac_file",
	};
	int i, num_fields = ARRAY_SIZE(fields);

	if (arg == 1) {
		char **res;

		res = os_calloc(num_fields + 1, sizeof(char *));
		if (!res)
			return NULL;
		for (i = 0; i < num_fields; i++) {
			res[i] = os_strdup(fields[i]);
			if (!res[i])
				return res;
		}
		return res;
	}
	return NULL;
}