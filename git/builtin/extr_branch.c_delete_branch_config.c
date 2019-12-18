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

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ git_config_rename_section (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void delete_branch_config(const char *branchname)
{
	struct strbuf buf = STRBUF_INIT;
	strbuf_addf(&buf, "branch.%s", branchname);
	if (git_config_rename_section(buf.buf, NULL) < 0)
		warning(_("Update of config-file failed"));
	strbuf_release(&buf);
}