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
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_realpath (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

void strbuf_add_real_path(struct strbuf *sb, const char *path)
{
	if (sb->len) {
		struct strbuf resolved = STRBUF_INIT;
		strbuf_realpath(&resolved, path, 1);
		strbuf_addbuf(sb, &resolved);
		strbuf_release(&resolved);
	} else
		strbuf_realpath(sb, path, 1);
}