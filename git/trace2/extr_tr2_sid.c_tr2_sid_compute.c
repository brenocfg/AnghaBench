#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  buf; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  TR2_ENVVAR_PARENT_SID ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addch (TYPE_1__*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  tr2_sid_append_my_sid_component () ; 
 TYPE_1__ tr2sid_buf ; 
 int /*<<< orphan*/  tr2sid_nr_git_parents ; 

__attribute__((used)) static void tr2_sid_compute(void)
{
	const char *parent_sid;

	if (tr2sid_buf.len)
		return;

	parent_sid = getenv(TR2_ENVVAR_PARENT_SID);
	if (parent_sid && *parent_sid) {
		const char *p;
		for (p = parent_sid; *p; p++)
			if (*p == '/')
				tr2sid_nr_git_parents++;

		strbuf_addstr(&tr2sid_buf, parent_sid);
		strbuf_addch(&tr2sid_buf, '/');
		tr2sid_nr_git_parents++;
	}

	tr2_sid_append_my_sid_component();

	setenv(TR2_ENVVAR_PARENT_SID, tr2sid_buf.buf, 1);
}