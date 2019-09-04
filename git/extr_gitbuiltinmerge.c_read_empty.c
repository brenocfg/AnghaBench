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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 char* empty_tree_oid_hex () ; 
 char* oid_to_hex (struct object_id const*) ; 
 scalar_t__ run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_empty(const struct object_id *oid, int verbose)
{
	int i = 0;
	const char *args[7];

	args[i++] = "read-tree";
	if (verbose)
		args[i++] = "-v";
	args[i++] = "-m";
	args[i++] = "-u";
	args[i++] = empty_tree_oid_hex();
	args[i++] = oid_to_hex(oid);
	args[i] = NULL;

	if (run_command_v_opt(args, RUN_GIT_CMD))
		die(_("read-tree failed"));
}