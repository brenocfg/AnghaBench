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
struct stash_info {int /*<<< orphan*/  w_commit; } ;
struct pathspec {int dummy; } ;
typedef  int /*<<< orphan*/  ps ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  check_changes_tracked_files (struct pathspec*) ; 
 int do_create_stash (struct pathspec*,struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stash_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pathspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf_ln (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_join_argv (struct strbuf*,int,char const**,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int create_stash(int argc, const char **argv, const char *prefix)
{
	int ret = 0;
	struct strbuf stash_msg_buf = STRBUF_INIT;
	struct stash_info info;
	struct pathspec ps;

	/* Starting with argv[1], since argv[0] is "create" */
	strbuf_join_argv(&stash_msg_buf, argc - 1, ++argv, ' ');

	memset(&ps, 0, sizeof(ps));
	if (!check_changes_tracked_files(&ps))
		return 0;

	ret = do_create_stash(&ps, &stash_msg_buf, 0, 0, &info,
			      NULL, 0);
	if (!ret)
		printf_ln("%s", oid_to_hex(&info.w_commit));

	strbuf_release(&stash_msg_buf);
	return ret;
}