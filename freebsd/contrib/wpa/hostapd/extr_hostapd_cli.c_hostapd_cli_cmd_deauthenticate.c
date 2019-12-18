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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int wpa_ctrl_command (struct wpa_ctrl*,char*) ; 

__attribute__((used)) static int hostapd_cli_cmd_deauthenticate(struct wpa_ctrl *ctrl, int argc,
					  char *argv[])
{
	char buf[64];
	if (argc < 1) {
		printf("Invalid 'deauthenticate' command - exactly one "
		       "argument, STA address, is required.\n");
		return -1;
	}
	if (argc > 1)
		os_snprintf(buf, sizeof(buf), "DEAUTHENTICATE %s %s",
			    argv[0], argv[1]);
	else
		os_snprintf(buf, sizeof(buf), "DEAUTHENTICATE %s", argv[0]);
	return wpa_ctrl_command(ctrl, buf);
}