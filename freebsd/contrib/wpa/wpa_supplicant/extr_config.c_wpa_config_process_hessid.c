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
struct wpa_config {int /*<<< orphan*/  hessid; } ;
struct global_parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ hwaddr_aton2 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,char const*) ; 

__attribute__((used)) static int wpa_config_process_hessid(
	const struct global_parse_data *data,
	struct wpa_config *config, int line, const char *pos)
{
	if (hwaddr_aton2(pos, config->hessid) < 0) {
		wpa_printf(MSG_ERROR, "Line %d: Invalid hessid '%s'",
			   line, pos);
		return -1;
	}

	return 0;
}