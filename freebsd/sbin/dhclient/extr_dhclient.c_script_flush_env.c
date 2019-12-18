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
struct client_state {scalar_t__ scriptEnvsize; int /*<<< orphan*/ ** scriptEnv; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
script_flush_env(struct client_state *client)
{
	int i;

	for (i = 0; client->scriptEnv[i]; i++) {
		free(client->scriptEnv[i]);
		client->scriptEnv[i] = NULL;
	}
	client->scriptEnvsize = 0;
}