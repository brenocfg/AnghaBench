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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 char* oid_to_hex (struct object_id const*) ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reset_for_rollback(const struct object_id *oid)
{
	const char *argv[4];	/* reset --merge <arg> + NULL */

	argv[0] = "reset";
	argv[1] = "--merge";
	argv[2] = oid_to_hex(oid);
	argv[3] = NULL;
	return run_command_v_opt(argv, RUN_GIT_CMD);
}