#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TR2_ENVVAR_PARENT_NAME ; 
 char* getenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addch (TYPE_1__*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 
 TYPE_1__ tr2cmdname_hierarchy ; 

void tr2_cmd_name_append_hierarchy(const char *name)
{
	const char *parent_name = getenv(TR2_ENVVAR_PARENT_NAME);

	strbuf_reset(&tr2cmdname_hierarchy);
	if (parent_name && *parent_name) {
		strbuf_addstr(&tr2cmdname_hierarchy, parent_name);
		strbuf_addch(&tr2cmdname_hierarchy, '/');
	}
	strbuf_addstr(&tr2cmdname_hierarchy, name);

	setenv(TR2_ENVVAR_PARENT_NAME, tr2cmdname_hierarchy.buf, 1);
}