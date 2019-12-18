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
struct rbcfg_env {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct rbcfg_env*) ; 
 int RB_ERR_INVALID ; 
 int rbcfg_env_set (struct rbcfg_env const*,char const*) ; 
 struct rbcfg_env* rbcfg_envs ; 
 int rbcfg_update (int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static int
rbcfg_cmd_set(int argc, const char *argv[])
{
	int err = RB_ERR_INVALID;
	int i;

	if (argc != 2) {
		/* not enough parameters */
		usage();
		return RB_ERR_INVALID;
	}

	for (i = 0; i < ARRAY_SIZE(rbcfg_envs); i++) {
		const struct rbcfg_env *env = &rbcfg_envs[i];

		if (strcmp(env->name, argv[0]))
			continue;

		err = rbcfg_env_set(env, argv[1]);
		if (err == 0)
			err = rbcfg_update(1);
		break;
	}

	return err;
}