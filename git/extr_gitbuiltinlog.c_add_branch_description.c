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
struct strbuf {scalar_t__ len; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  read_branch_desc (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void add_branch_description(struct strbuf *buf, const char *branch_name)
{
	struct strbuf desc = STRBUF_INIT;
	if (!branch_name || !*branch_name)
		return;
	read_branch_desc(&desc, branch_name);
	if (desc.len) {
		strbuf_addch(buf, '\n');
		strbuf_addbuf(buf, &desc);
		strbuf_addch(buf, '\n');
	}
	strbuf_release(&desc);
}