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
struct wpa_config {int* sae_groups; } ;
struct global_parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int* wpa_config_parse_int_array (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,char const*) ; 

__attribute__((used)) static int wpa_config_process_sae_groups(
	const struct global_parse_data *data,
	struct wpa_config *config, int line, const char *pos)
{
	int *groups = wpa_config_parse_int_array(pos);
	if (groups == NULL) {
		wpa_printf(MSG_ERROR, "Line %d: Invalid sae_groups '%s'",
			   line, pos);
		return -1;
	}

	os_free(config->sae_groups);
	config->sae_groups = groups;

	return 0;
}