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
struct wpa_config {char* country; } ;
struct global_parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wpa_config_process_country(const struct global_parse_data *data,
				      struct wpa_config *config, int line,
				      const char *pos)
{
	if (!pos[0] || !pos[1]) {
		wpa_printf(MSG_DEBUG, "Invalid country set");
		return -1;
	}
	config->country[0] = pos[0];
	config->country[1] = pos[1];
	wpa_printf(MSG_DEBUG, "country='%c%c'",
		   config->country[0], config->country[1]);
	return 0;
}