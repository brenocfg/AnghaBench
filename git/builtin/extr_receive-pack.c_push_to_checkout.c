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
struct argv_array {int /*<<< orphan*/  argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  absolute_path (char const*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_to_hex (unsigned char*) ; 
 int /*<<< orphan*/  push_to_checkout_hook ; 
 scalar_t__ run_hook_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *push_to_checkout(unsigned char *hash,
				    struct argv_array *env,
				    const char *work_tree)
{
	argv_array_pushf(env, "GIT_WORK_TREE=%s", absolute_path(work_tree));
	if (run_hook_le(env->argv, push_to_checkout_hook,
			hash_to_hex(hash), NULL))
		return "push-to-checkout hook declined";
	else
		return NULL;
}