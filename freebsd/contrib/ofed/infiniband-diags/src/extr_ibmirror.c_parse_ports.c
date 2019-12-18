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
 int MAX_SWITCH_PORTS ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char*) ; 
 char* strtok (char*,char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_ports(char *ports_str, char *ports_array)
{
	int num, i;
	char *str = strdup(ports_str);
	char *token = strtok(str, ",");
	for (i = 0; i < MAX_SWITCH_PORTS && token; i++) {
		num = strtoul(token, NULL, 0);
		if (num > 0 && num < MAX_SWITCH_PORTS)
			ports_array[num] = 1;

		token = strtok(NULL, ",");
	}
	free(str);
	return 0;
}