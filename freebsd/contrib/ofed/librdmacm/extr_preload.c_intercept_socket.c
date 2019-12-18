#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int domain; int type; int protocol; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int SOCK_DGRAM ; 
 int SOCK_STREAM ; 
 TYPE_1__* config ; 
 int config_cnt ; 
 int /*<<< orphan*/  program_invocation_short_name ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intercept_socket(int domain, int type, int protocol)
{
	int i;

	if (!config_cnt)
		return 1;

	if (!protocol) {
		if (type == SOCK_STREAM)
			protocol = IPPROTO_TCP;
		else if (type == SOCK_DGRAM)
			protocol = IPPROTO_UDP;
	}

	for (i = 0; i < config_cnt; i++) {
		if ((!config[i].name ||
		     !strncasecmp(config[i].name, program_invocation_short_name,
				  strlen(config[i].name))) &&
		    (!config[i].domain || config[i].domain == domain) &&
		    (!config[i].type || config[i].type == type) &&
		    (!config[i].protocol || config[i].protocol == protocol))
			return 1;
	}

	return 0;
}