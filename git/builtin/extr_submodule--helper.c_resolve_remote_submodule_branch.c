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
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 char* remote_submodule_branch (char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int resolve_remote_submodule_branch(int argc, const char **argv,
		const char *prefix)
{
	const char *ret;
	struct strbuf sb = STRBUF_INIT;
	if (argc != 2)
		die("submodule--helper remote-branch takes exactly one arguments, got %d", argc);

	ret = remote_submodule_branch(argv[1]);
	if (!ret)
		die("submodule %s doesn't exist", argv[1]);

	printf("%s", ret);
	strbuf_release(&sb);
	return 0;
}