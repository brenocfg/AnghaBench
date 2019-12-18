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
struct TYPE_2__ {int /*<<< orphan*/  u32; } ;
struct rbcfg_value {TYPE_1__ val; } ;
struct rbcfg_env {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int RB_ERR_INVALID ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  rbcfg_ctx ; 
 struct rbcfg_value* rbcfg_env_find (struct rbcfg_env const*,char const*) ; 
 int rbcfg_set_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
rbcfg_env_set_u32(const struct rbcfg_env *env, const char *data)
{
	const struct rbcfg_value *v;
	int err;

	v = rbcfg_env_find(env, data);
	if (v == NULL) {
		fprintf(stderr, "invalid value '%s'\n", data);
		return RB_ERR_INVALID;
	}

	err = rbcfg_set_u32(rbcfg_ctx, env->id, v->val.u32);
	return err;
}