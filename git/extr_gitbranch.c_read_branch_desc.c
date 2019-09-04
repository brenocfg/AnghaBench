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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ git_config_get_string (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

int read_branch_desc(struct strbuf *buf, const char *branch_name)
{
	char *v = NULL;
	struct strbuf name = STRBUF_INIT;
	strbuf_addf(&name, "branch.%s.description", branch_name);
	if (git_config_get_string(name.buf, &v)) {
		strbuf_release(&name);
		return -1;
	}
	strbuf_addstr(buf, v);
	free(v);
	strbuf_release(&name);
	return 0;
}