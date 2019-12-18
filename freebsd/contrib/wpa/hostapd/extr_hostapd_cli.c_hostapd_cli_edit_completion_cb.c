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
 char** hostapd_cli_cmd_completion (char*,char const*,int) ; 
 char** list_cmd_list () ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,int) ; 
 char* os_strchr (char const*,char) ; 

__attribute__((used)) static char ** hostapd_cli_edit_completion_cb(void *ctx, const char *str,
					      int pos)
{
	char **res;
	const char *end;
	char *cmd;

	end = os_strchr(str, ' ');
	if (end == NULL || str + pos < end)
		return list_cmd_list();

	cmd = os_malloc(pos + 1);
	if (cmd == NULL)
		return NULL;
	os_memcpy(cmd, str, pos);
	cmd[end - str] = '\0';
	res = hostapd_cli_cmd_completion(cmd, str, pos);
	os_free(cmd);
	return res;
}