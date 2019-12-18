#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cmd; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* hostapd_cli_commands ; 
 char** os_calloc (int,int) ; 
 char* os_strdup (scalar_t__) ; 

__attribute__((used)) static char ** list_cmd_list(void)
{
	char **res;
	int i, count;

	count = ARRAY_SIZE(hostapd_cli_commands);
	res = os_calloc(count + 1, sizeof(char *));
	if (res == NULL)
		return NULL;

	for (i = 0; hostapd_cli_commands[i].cmd; i++) {
		res[i] = os_strdup(hostapd_cli_commands[i].cmd);
		if (res[i] == NULL)
			break;
	}

	return res;
}