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
struct wpa_ctrl {int dummy; } ;

/* Variables and functions */
 int hostapd_cli_cmd (struct wpa_ctrl*,char*,int,int,char**) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int hostapd_cli_cmd_req_range(struct wpa_ctrl *ctrl, int argc,
				     char *argv[])
{
	if (argc < 4) {
		printf("Invalid req_range command: needs at least 4 arguments - dest address, randomization interval, min AP count, and 1 to 16 AP addresses\n");
		return -1;
	}

	return hostapd_cli_cmd(ctrl, "REQ_RANGE", 4, argc, argv);
}