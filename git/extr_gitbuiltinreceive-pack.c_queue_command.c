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
struct command {struct command* next; int /*<<< orphan*/  new_oid; int /*<<< orphan*/  old_oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct command*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 int /*<<< orphan*/  ref_name ; 

__attribute__((used)) static struct command **queue_command(struct command **tail,
				      const char *line,
				      int linelen)
{
	struct object_id old_oid, new_oid;
	struct command *cmd;
	const char *refname;
	int reflen;
	const char *p;

	if (parse_oid_hex(line, &old_oid, &p) ||
	    *p++ != ' ' ||
	    parse_oid_hex(p, &new_oid, &p) ||
	    *p++ != ' ')
		die("protocol error: expected old/new/ref, got '%s'", line);

	refname = p;
	reflen = linelen - (p - line);
	FLEX_ALLOC_MEM(cmd, ref_name, refname, reflen);
	oidcpy(&cmd->old_oid, &old_oid);
	oidcpy(&cmd->new_oid, &new_oid);
	*tail = cmd;
	return &cmd->next;
}