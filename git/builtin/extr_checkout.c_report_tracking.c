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
struct branch_info {int /*<<< orphan*/  name; } ;
struct branch {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHEAD_BEHIND_FULL ; 
 struct strbuf STRBUF_INIT ; 
 struct branch* branch_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_tracking_info (struct branch*,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void report_tracking(struct branch_info *new_branch_info)
{
	struct strbuf sb = STRBUF_INIT;
	struct branch *branch = branch_get(new_branch_info->name);

	if (!format_tracking_info(branch, &sb, AHEAD_BEHIND_FULL))
		return;
	fputs(sb.buf, stdout);
	strbuf_release(&sb);
}