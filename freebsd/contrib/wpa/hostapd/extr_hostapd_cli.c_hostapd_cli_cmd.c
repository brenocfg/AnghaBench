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
 int /*<<< orphan*/  printf (char*,char const*,int,char*) ; 
 int wpa_ctrl_command (struct wpa_ctrl*,char*) ; 
 scalar_t__ write_cmd (char*,int,char const*,int,char**) ; 

__attribute__((used)) static int hostapd_cli_cmd(struct wpa_ctrl *ctrl, const char *cmd,
			   int min_args, int argc, char *argv[])
{
	char buf[4096];

	if (argc < min_args) {
		printf("Invalid %s command - at least %d argument%s required.\n",
		       cmd, min_args, min_args > 1 ? "s are" : " is");
		return -1;
	}
	if (write_cmd(buf, sizeof(buf), cmd, argc, argv) < 0)
		return -1;
	return wpa_ctrl_command(ctrl, buf);
}