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
 int /*<<< orphan*/  create_temp_file (struct object_id*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_default_config ; 
 int /*<<< orphan*/  puts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  usage (char*) ; 

int cmd_unpack_file(int argc, const char **argv, const char *prefix)
{
	struct object_id oid;

	if (argc != 2 || !strcmp(argv[1], "-h"))
		usage("git unpack-file <sha1>");
	if (get_oid(argv[1], &oid))
		die("Not a valid object name %s", argv[1]);

	git_config(git_default_config, NULL);

	puts(create_temp_file(&oid));
	return 0;
}