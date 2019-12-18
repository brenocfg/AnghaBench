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
struct tmp_objdir {int /*<<< orphan*/  path; } ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  get_object_directory () ; 
 int migrate_paths (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  tmp_objdir_destroy (struct tmp_objdir*) ; 

int tmp_objdir_migrate(struct tmp_objdir *t)
{
	struct strbuf src = STRBUF_INIT, dst = STRBUF_INIT;
	int ret;

	if (!t)
		return 0;

	strbuf_addbuf(&src, &t->path);
	strbuf_addstr(&dst, get_object_directory());

	ret = migrate_paths(&src, &dst);

	strbuf_release(&src);
	strbuf_release(&dst);

	tmp_objdir_destroy(t);
	return ret;
}