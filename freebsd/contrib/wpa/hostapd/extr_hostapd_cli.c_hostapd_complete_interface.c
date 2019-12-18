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
 int /*<<< orphan*/  DEFINE_DL_LIST (int /*<<< orphan*/ ) ; 
 char** cli_txt_list_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cli_txt_list_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctrl_conn ; 
 int get_cmd_arg_num (char const*,int) ; 
 int /*<<< orphan*/  hostapd_cli_get_interfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  interfaces ; 

__attribute__((used)) static char ** hostapd_complete_interface(const char *str, int pos)
{
	int arg = get_cmd_arg_num(str, pos);
	char **res = NULL;
	DEFINE_DL_LIST(interfaces);

	switch (arg) {
	case 1:
		hostapd_cli_get_interfaces(ctrl_conn, &interfaces);
		res = cli_txt_list_array(&interfaces);
		cli_txt_list_flush(&interfaces);
		break;
	}

	return res;
}