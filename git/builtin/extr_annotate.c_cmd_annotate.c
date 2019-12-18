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
struct argv_array {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char const*) ; 
 int /*<<< orphan*/  argv_array_pushl (struct argv_array*,char*,char*,int /*<<< orphan*/ *) ; 
 int cmd_blame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

int cmd_annotate(int argc, const char **argv, const char *prefix)
{
	struct argv_array args = ARGV_ARRAY_INIT;
	int i;

	argv_array_pushl(&args, "annotate", "-c", NULL);

	for (i = 1; i < argc; i++) {
		argv_array_push(&args, argv[i]);
	}

	return cmd_blame(args.argc, args.argv, prefix);
}