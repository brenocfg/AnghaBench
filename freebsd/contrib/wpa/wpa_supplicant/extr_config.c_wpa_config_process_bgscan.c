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
struct wpa_config {int dummy; } ;
struct global_parse_data {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* wpa_config_parse_string (char const*,size_t*) ; 
 int wpa_global_config_parse_str (struct global_parse_data const*,struct wpa_config*,int,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_config_process_bgscan(const struct global_parse_data *data,
				     struct wpa_config *config, int line,
				     const char *pos)
{
	size_t len;
	char *tmp;
	int res;

	tmp = wpa_config_parse_string(pos, &len);
	if (tmp == NULL) {
		wpa_printf(MSG_ERROR, "Line %d: failed to parse %s",
			   line, data->name);
		return -1;
	}

	res = wpa_global_config_parse_str(data, config, line, tmp);
	os_free(tmp);
	return res;
}