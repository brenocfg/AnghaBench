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
typedef  int uint32_t ;
struct rbcfg_value {char const* name; } ;
struct rbcfg_env {char* name; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  rbcfg_ctx ; 
 struct rbcfg_value* rbcfg_env_find_u32 (struct rbcfg_env const*,int) ; 
 int rbcfg_get_u32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static const char *
rbcfg_env_get_u32(const struct rbcfg_env *env)
{
	const struct rbcfg_value *v;
	uint32_t val;
	int err;

	err = rbcfg_get_u32(rbcfg_ctx, env->id, &val);
	if (err)
		return NULL;

	v = rbcfg_env_find_u32(env, val);
	if (v == NULL) {
		fprintf(stderr, "unknown value %08x found for %s\n",
			val, env->name);
		return NULL;
	}

	return v->name;
}