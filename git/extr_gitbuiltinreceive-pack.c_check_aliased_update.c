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
struct string_list {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct command {int /*<<< orphan*/  ref_name; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  check_aliased_update_internal (struct command*,struct string_list*,char const*,int) ; 
 int /*<<< orphan*/  get_git_namespace () ; 
 char* resolve_ref_unsafe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void check_aliased_update(struct command *cmd, struct string_list *list)
{
	struct strbuf buf = STRBUF_INIT;
	const char *dst_name;
	int flag;

	strbuf_addf(&buf, "%s%s", get_git_namespace(), cmd->ref_name);
	dst_name = resolve_ref_unsafe(buf.buf, 0, NULL, &flag);
	check_aliased_update_internal(cmd, list, dst_name, flag);
	strbuf_release(&buf);
}