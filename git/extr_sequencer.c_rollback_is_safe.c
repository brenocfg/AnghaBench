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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 scalar_t__ get_oid_hex (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  git_path_abort_safety_file () ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 int oideq (struct object_id*,struct object_id*) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 

__attribute__((used)) static int rollback_is_safe(void)
{
	struct strbuf sb = STRBUF_INIT;
	struct object_id expected_head, actual_head;

	if (strbuf_read_file(&sb, git_path_abort_safety_file(), 0) >= 0) {
		strbuf_trim(&sb);
		if (get_oid_hex(sb.buf, &expected_head)) {
			strbuf_release(&sb);
			die(_("could not parse %s"), git_path_abort_safety_file());
		}
		strbuf_release(&sb);
	}
	else if (errno == ENOENT)
		oidclr(&expected_head);
	else
		die_errno(_("could not read '%s'"), git_path_abort_safety_file());

	if (get_oid("HEAD", &actual_head))
		oidclr(&actual_head);

	return oideq(&actual_head, &expected_head);
}