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
struct interface_info {char const* name; TYPE_1__* client; } ;
struct TYPE_2__ {int scriptEnvsize; int /*<<< orphan*/ ** scriptEnv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_PATH ; 
 int /*<<< orphan*/  error (char*) ; 
 struct interface_info* ifi ; 
 int /*<<< orphan*/ ** malloc (int) ; 
 int /*<<< orphan*/  script_set_env (TYPE_1__*,char*,char*,char const*) ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 

void
priv_script_init(const char *reason, char *medium)
{
	struct interface_info *ip = ifi;

	if (ip) {
		ip->client->scriptEnvsize = 100;
		if (ip->client->scriptEnv == NULL)
			ip->client->scriptEnv =
			    malloc(ip->client->scriptEnvsize * sizeof(char *));
		if (ip->client->scriptEnv == NULL)
			error("script_init: no memory for environment");

		ip->client->scriptEnv[0] = strdup(CLIENT_PATH);
		if (ip->client->scriptEnv[0] == NULL)
			error("script_init: no memory for environment");

		ip->client->scriptEnv[1] = NULL;

		script_set_env(ip->client, "", "interface", ip->name);

		if (medium)
			script_set_env(ip->client, "", "medium", medium);

		script_set_env(ip->client, "", "reason", reason);
	}
}