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
struct branch_info {int /*<<< orphan*/  path; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERPRET_BRANCH_LOCAL ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_branchname (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_branch_path(struct branch_info *branch)
{
	struct strbuf buf = STRBUF_INIT;

	strbuf_branchname(&buf, branch->name, INTERPRET_BRANCH_LOCAL);
	if (strcmp(buf.buf, branch->name))
		branch->name = xstrdup(buf.buf);
	strbuf_splice(&buf, 0, 0, "refs/heads/", 11);
	branch->path = strbuf_detach(&buf, NULL);
}